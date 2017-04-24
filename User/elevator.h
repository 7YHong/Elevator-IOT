//
// Created by QYH on 2017/4/23.
//

#ifndef ELEVATOR_ELEVATOR_H
#define ELEVATOR_ELEVATOR_H

#include "includes.h"

typedef struct {
    unsigned short waitlist;
    //status表示状态
    //-1:下降
    //0:不动
    //1:上升
    short status;
    short current;
    bool dooropen;    //电梯门状态，0说明门关着
}Elevator;

extern Elevator elevator1,elevator2;

void AddTarget(Elevator *e, short target);
void StartElevator(Elevator *e);

#endif //ELEVATOR32_ELEVATOR_H
