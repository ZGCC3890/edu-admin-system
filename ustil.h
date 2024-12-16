//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_USTIL_H
#define CPP_SE_USTIL_H
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>
#include "graphFunctions.h"

#define CommonBlue RGB(50, 100, 200)
#define LightBlue RGB(70, 120, 210)

//界面枚举类
enum class MENU{
    STUDENT_MGMT,
    TEACHER_MGMT,
    ANNOUNCE_MGMT,
    USER_MGMT,
    END
};

//鼠标信息结构体
extern ExMessage msg;

//当前界面
extern MENU curGraph;

//sql查询结果
extern pqxx::result res;

//读取config
std::string LoadConfig();
//从config文件读取配置，建立连接
std::pair<std::string, std::string> EstablishConnection(const std::string& filename);

//绘制菜单
void Menu(int n);
//菜单选择
MENU MenuChoose();

#endif //CPP_SE_USTIL_H
