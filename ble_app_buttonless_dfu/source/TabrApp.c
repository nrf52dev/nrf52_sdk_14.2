#include "TabrApp.h"
#include "stdio.h"
#include "string.h"
#include "nrf_fstorage_sd.h"
#include "nrf_fstorage.h"
#include "nrf_pwr_mgmt.h"

SYS_CONFIG sys_config;


static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);


NRF_FSTORAGE_DEF(nrf_fstorage_t fstorage) =
{
    /* Set a handler for fstorage events. */
    .evt_handler = fstorage_evt_handler,

    /* These below are the boundaries of the flash space assigned to this instance of fstorage.
     * You must set these manually, even at runtime, before nrf_fstorage_init() is called.
     * The function nrf5_flash_end_addr_get() can be used to retrieve the last address on the
     * last page of flash available to write data. */
    .start_addr = 0x77000,
    .end_addr   = 0x77fff,
};

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{
    if (p_evt->result != NRF_SUCCESS)
    {
        //NRF_LOG_INFO("--> Event received: ERROR while executing an fstorage operation.");
        return;
    }

    switch (p_evt->id)
    {
        case NRF_FSTORAGE_EVT_WRITE_RESULT:
        {
            //NRF_LOG_INFO("--> Event received: wrote %d bytes at address 0x%x.",
                        // p_evt->len, p_evt->addr);
        } break;

        case NRF_FSTORAGE_EVT_ERASE_RESULT:
        {
           // NRF_LOG_INFO("--> Event received: erased %d page from address 0x%x.",
                        //p_evt->len, p_evt->addr);
        } break;

        default:
            break;
    }
}
void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage)
{
    /* While fstorage is busy, sleep and wait for an event. */
    while (nrf_fstorage_is_busy(p_fstorage))
    {
        nrf_pwr_mgmt_run();
    }
}
void TabrApp_InitAppFlash(void)
{
	nrf_fstorage_api_t * p_fs_api = &nrf_fstorage_sd;
	nrf_fstorage_init(&fstorage, p_fs_api, NULL);
}
void TabrApp_WriteAllDataToFlash()
{
	ret_code_t ret_code;
	ret_code = nrf_fstorage_erase(&fstorage, 0x77000,1, NULL);
	wait_for_flash_ready(&fstorage);
  ret_code = nrf_fstorage_write(&fstorage, 0x77000, &sys_config, sizeof(SYS_CONFIG), NULL);
	wait_for_flash_ready(&fstorage);
}

// ?????
uint8_t str_cmp(uint8_t *p1,uint8_t *p2,uint8_t len)
{
    uint8_t i=0;
    while(i<len){
      if(p1[i]!=p2[i])
        return 0;
      i++;
    }
    return 1;
}

uint8_t TabrApp_ReadAllDataFromeFlash(void)
{
	ret_code_t ret_code;
	ret_code = nrf_fstorage_read(&fstorage,0x77000,&sys_config,sizeof(SYS_CONFIG));
	wait_for_flash_ready(&fstorage);
    if(ret_code != NRF_SUCCESS)
    {
      return 0;
    }
    else
    {
      if(str_cmp(sys_config.config_name,(uint8_t*)"TABR",4) != 1 || sys_config.config_version != CONFIG_VERSION)
        return 0;
      else
        return 1;
    }
}
void TabrApp_SetAllParaDefault(void)    
{
  memset(&sys_config,0,sizeof(sys_config));
  uint8_t config_name[4]= "TABR";  
  memcpy(sys_config.config_name,config_name,4);
  sys_config.config_version = CONFIG_VERSION;
  
  sys_config.baseVol = 2.039;
  sys_config.unitVol = 0.0420;
  
  sys_config.volPressureMap[0].pressure = 0.0f;
  sys_config.volPressureMap[0].vol = 0.150f;
  sys_config.volPressureMap[0].used = 1;
  
  sys_config.volPressureMap[1].pressure = 5.0f;
  sys_config.volPressureMap[2].pressure = 6.0f;
  sys_config.volPressureMap[3].pressure = 7.0f;
  sys_config.volPressureMap[4].pressure = 10.0f;
  sys_config.volPressureMap[5].pressure = 15.0f;
  sys_config.volPressureMap[6].pressure = 20.0f;
  sys_config.volPressureMap[7].pressure = 25.0f;
  sys_config.volPressureMap[8].pressure = 30.0f;
  sys_config.volPressureMap[9].pressure = 35.0f;
  sys_config.volPressureMap[10].pressure = 40.0f;
  
	sys_config.cnt_r = 0;
  TabrApp_WriteAllDataToFlash();
}
