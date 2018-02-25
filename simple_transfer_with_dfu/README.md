1. 功能

1.1 带Nordic支持的DFU，通过nRF Connect手机APP升级；

1.2 服务UUID为0xfff0；通知特性的UUID为0xfff4，每个通知包最大20字节；可写入特性的UUID为0xfff1，每个写入包最大20字节；

1.3 每个写入包的首字节的会点亮或熄灭LED，bit3-LED3, bit2-LED2, bit1-LED1；

1.4 以1秒的间隔发送20字节的通知包；


2. 代码

2.1 放到example/peripheral/下，可直接编译，无需修改底层；

2.2 透传的代码放在ble_lbs.c，与原始的ble_lbs.c隔离开；

2.3 发送20字节通知的代码在main.c的notification_handler函数；

2.4 接收20字节写入的代码在ble_lbs.c的on_write函数；

2.5 注意：在初始化广播时，需要把两个服务（透传和DFU）的UUID添加进来，即main.c的全局数组m_adv_uuids。

