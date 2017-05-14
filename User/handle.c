//
// Created by QYH on 2017/5/12.
//

#include "includes.h"

short stat = 0;

void resetWifi(){
	PBout(1)=0;
	osDelay(100);
	PBout(1)=1;
}

void handleStatus(char *action, char index, char data) {
    printf("action:%s, index:%d, data:%d\n", action, index, data);
}

void handleTcp(char *msg) {
    if (strcmp(msg, "CLOSED") == 0) stat=0;
    switch (stat) {
        case 0:
            if (strcmp(msg, "WIFI GOT IP") == 0) {
                stat = 1;
                Uprint("ATE0\r\n");
                osDelay(1000);
                Uprint("AT+CIPMODE=1\r\n");
                osDelay(1000);
                Uprint("AT+CIPSTART=\"TCP\",\"192.168.1.107\",8080\r\n");
            }
            break;
        case 1://连接上了WIFI
            if (strcmp(msg, "CONNECT") == 0) {
                stat = 2;
                printf("AT+CIPSEND\r\n");
            }
            break;
        case 2://连接上了TCP
            if (strcmp(msg, ">")) return;
            stat = 3;
            break;
        case 3://进入了透传模式
            PCprint(msg);
            break;
    }
}
