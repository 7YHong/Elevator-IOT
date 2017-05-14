#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#include "GPIOLIKE51.h"
#include "bsp.h"
#include "usart.h"
#include "spi.h"
#include "key.h"
#include "handle.h"


#define ACTION_STATUS "status"
#define INDEX_REMOTECTL 1
#define INDEX_STATUS 2
#define INDEX_DOOR 3
#define INDEX_ARRIVE 4
#define ACTION_BTNUP "btnup"
#define ACTION_BTNDOWN "btndown"
#define ACTION_BTNINDOOR "btnindoor"
//遵循电梯状态转换图
enum Estatus {
    PEND, MOVE, DOOR
};
//电梯运行数据
typedef struct {
    bool waitlist[8];
    enum Estatus estatus;
    //status表示状态
    //-1:下降
    //0:不动
    //1:上升
    short status;
    short arrive;
    short door;    //电梯门状态，0说明门关着
} Elevator;


extern Elevator elevator;
#endif