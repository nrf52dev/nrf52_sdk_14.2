1. 安装必要的软件

1.1 Keil 5: https://www.keil.com/download/

1.2 nRFgo Studio: http://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832

1.3 nRF5x-Command-Line-Tools: http://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832

1.4 nRF SDK v14.2.0: http://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832


2. 开发规约

2.1 全部产品基于Keil5/SDK14.2开发；

2.2 不得修改底层代码，如果必须，请拷贝出来，与main.c放在一起，再修改；

2.3 本代码仓库不包含底层代码，拷贝到SDKv14.2的examples\ble_peripheral目录下，才能正常使用；

2.4 放在examples\ble_peripheral下的工程，必须能直接编译下载，无需二次配置；

2.5 只上传源文件和配置文件，不要上传OBJ和HEX文件，以及其它的大体积中间文件；


（待续）
