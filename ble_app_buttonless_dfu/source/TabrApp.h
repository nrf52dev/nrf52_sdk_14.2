#ifndef TABR_APP_H
#define TABR_APP_H

#include "stdint.h"

#define BLE_SCBA_VERSION_DEVICE	2
#define BLE_SCBA_VERSION_HARD		0
#define BLE_SCBA_VERSION_SOFT		0

#define CONFIG_VERSION 1

enum SCBA_WORK_STATE
{
	SCBA_INIT_CONFIG_STATE = 0,
	SCBA_CONNTED,
	SCBA_ADJ,
	SCBA_STANDBY,
	SCBA_WORK_RECHECK,
	SCBA_WORK,
};

typedef struct
{
	float vol;
	float pressure;
	unsigned char used;
}VOL_PRE_PAIR;

typedef struct
{
	uint8_t config_name[4];
	uint8_t config_version;
	unsigned char cnt_r;
	float baseVol;
	float unitVol;
	VOL_PRE_PAIR volPressureMap[11];
}SYS_CONFIG;	

extern SYS_CONFIG sys_config;
extern enum SCBA_WORK_STATE scba_work_state;// = SCBA_INIT_CONFIG_STATE;

extern void TabrApp_InitAppFlash(void);
extern void TabrApp_SetAllParaDefault(void);
extern void TabrApp_WriteAllDataToFlash(void);
extern uint8_t TabrApp_ReadAllDataFromeFlash(void);

#endif
