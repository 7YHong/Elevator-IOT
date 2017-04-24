#include "includes.h"

void KEY_Init(void) {

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA

    /*
    // A0-A3为输入
    */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //4列对应引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //普通入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//100M
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*
    // A4-A7为输出
    */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; //4行对应引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

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