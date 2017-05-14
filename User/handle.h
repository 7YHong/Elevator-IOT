//
// Created by QYH on 2017/5/12.
//

#ifndef ELEVATOR32_HANDLE_H
#define ELEVATOR32_HANDLE_H

//初始化WIFI的使能端
void resetWifi();
/**
 * 处理电梯运行产生的消息
 * 发送至监控端
 */
void handleStatus(char *action,char index,char data);
/**
 * 处理按钮按下的事件产生的消息
 */
void handleBtn(char *action,char index);
/**
 * 处理串口产生的消息
 */
void handleTcp(char *msg);

#endif //ELEVATOR32_HANDLE_H
