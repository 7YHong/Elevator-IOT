#include "includes.h"


short KeyScan(void) { //实现矩阵键盘。返回值为KeyVal，各按键的键值，此键值由用户自己定义。

    short KeyVal = 0;     //keyVal为最后返回的键值。
    short i;
    GPIO_Write(GPIOA, GPIOA->ODR & 0xff0f | 0xf0);//GPIOA4567为高,各行输出高电平	
    if ((GPIO_ReadInputData(GPIOA) & 0x0f) == 0)  //如果，PA0123全为0，则没有键按下。此时，返回值为-1.
        return -1;
    else {
        osDelay(10);//延时10ms去抖动。
        if ((GPIO_ReadInputData(GPIOA) & 0x0f) == 0)  //如果，延时10ms后，PB0123又全为0，则刚才引脚的电位变化是抖动产生的.
            return -1;
    }

    for (i = 0; i < 4; i++) {
        GPIO_Write(GPIOA, GPIOA->ODR & 0xff0f | 0x10 << i);//从PB4开始，每一行分别输出1.  
        switch (GPIO_ReadInputData(GPIOA) & 0x0f) {
            case 0x01:
                KeyVal = 4 * i + 4;
                break;
            case 0x02:
                KeyVal = 4 * i + 2;
                break;
            case 0x04:
                KeyVal = 4 * i + 3;
                break;
            case 0x08:
                KeyVal = 4 * i + 1;
                break;
        }
        while (GPIO_ReadInputData(GPIOA) & 0x0f) osDelay(10);        //松手检测
        if (KeyVal) return KeyVal;
    }
		return KeyVal;
}