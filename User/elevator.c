//
// Created by QYH on 2017/4/23.
//

#include "includes.h"
#include "elevator.h"

//Elevator elevator1={0,0,0,1}, elevator2={0,0,0,1};
Elevator elevator1, elevator2;

void UpdateStatus(Elevator *e) {
    //判断队列为空
    if (!e->waitlist) {
        e->status = 0;
        return;
    }
    //判断头尾
    if (e->waitlist < 1 << e->current) e->status = -1;
    else if ((e->waitlist & ((1 << e->current) - 1)) == 0) e->status = 1;

    //判断越界
    if (e->current == 8) {
        e->current = 6;
        e->status = -1;
    } else if (e->current == -1) {
        e->current = 1;
        e->status = 1;
    }
		/*
    printf("\ncurrent:%d\t", e->current);
    printf("status:%d\t", e->status);
    printf("door:%d\t", e->dooropen);
    printf("waitlist:%x\n", e->waitlist);
		*/
}

void GetDistance(Elevator *e, short target) {

}

/*
 * @para dooropen 0关门，1开门
 */
void SwichDoor(Elevator *e, bool dooropen) {
    /*if (dooropen) printf("open door...\n");
    else printf("close door...\n");
	  */

    e->dooropen = dooropen;
    osDelay(1000);
}

/*
 * 增加到达列表
 * 并且赋予初始方向
 */
void AddTarget(Elevator *e, short target) {
    if (target==e->current) {
        SwichDoor(e,1);
        return;
    }
    e->waitlist |= 1 << target;
    if (!e->status) {
        e->status = target > e->current ? 1 : -1;
    }
}

void StartElevator(Elevator *e) {
    for (;;) {
        UpdateStatus(e);
        if (e->dooropen) {   //门开着
            SwichDoor(e, 0);
            continue;
        }
        if (!e->status) {     //无状态
            osDelay(500);
            continue;
        }
        if (e->waitlist & 1 << e->current) { //到达目的层
            SwichDoor(e, 1);
            e->waitlist &= ~(1 << e->current);
            osDelay(5000);
            continue;
        }
        {
            e->current += e->status;
            osDelay(2000);
        }
    }
}