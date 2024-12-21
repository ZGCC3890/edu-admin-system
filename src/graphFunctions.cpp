//
// Created by ZGCC on 24-12-16.
//
#include "ustil.h"

void fillroundrect_(object x){
    fillroundrect(x.posx, x.posy, x.posx + x.width, x.posy + x.height, 10, 10);
}

void roundrect_(object x){
    roundrect(x.posx, x.posy, x.posx + x.width, x.posy + x.height, 10, 10);
}

void fillrectangle_(object x){
    fillrectangle(x.posx, x.posy, x.posx + x.width, x.posy + x.height);
}

void rectangle_(object x){
    rectangle(x.posx, x.posy, x.posx + x.width, x.posy + x.height);
}

bool isInside(ExMessage m, object x){
    if(m.x >= x.posx && m.x <= x.posx + x.width && m.y <= x.posy + x.height && m.y >= x.posy) return true;
    return false;
}

void OutputText(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st){
    settextcolor(color);
    settextstyle(nH,nW,st);
    outtextxy(x, y, str);
}

void ButtonAnimation(ExMessage m, object x, COLORREF colorOn, COLORREF colorOff, int lineWidth, std::string sort){
    if(isInside(m, x)){
        setlinecolor(colorOn);
        if(sort == "roundrect")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
        else if(sort == "rectangle")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
    }else{
        setlinecolor(colorOff);
        if(sort == "roundrect")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
        else if(sort == "rectangle")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
    }
}

void MenuAnimation(int n){
    if(msg.x >= 0 && msg.x <= 170) {
        if(msg.y >= 60 && msg.y <= 160 || n == 0)
            OutputText(25, 100, YELLOW, 20, 0, "学生选课模块", "宋体");
        else OutputText(25, 100, WHITE, 20, 0, "学生选课模块", "宋体");
        if(msg.y >= 160 && msg.y <= 260 || n == 1)
            OutputText(25, 200, YELLOW, 20, 0, "教师管理模块", "宋体");
        else OutputText(25, 200, WHITE, 20, 0, "教师管理模块", "宋体");
        if(msg.y >= 260 && msg.y <= 360 || n == 2)
            OutputText(25, 300, YELLOW, 20, 0, "公告管理模块", "宋体");
        else OutputText(25, 300, WHITE, 20, 0, "公告管理模块", "宋体");
        if(msg.y >= 360 && msg.y <= 460 || n == 3)
            OutputText(25, 400, YELLOW, 20, 0, "用户管理模块", "宋体");
        else OutputText(25, 400, WHITE, 20, 0, "用户管理模块", "宋体");
        if(msg.y >= 460 && msg.y <= 560 || n == 4)
            OutputText(25, 500, YELLOW, 20, 0, "考试管理模块", "宋体");
        else OutputText(25, 500, WHITE, 20, 0, "考试管理模块", "宋体");
        if(msg.y >= 760 && msg.y <= 860)
            OutputText(65, 800, YELLOW, 20, 0, "退出", "宋体");
        else OutputText(65, 800, WHITE, 20, 0, "退出", "宋体");
    }
}

void InitMouseMsg() {
    msg.x = 0, msg.y = 0;
}

void ClearWindow(){
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    fillrectangle_({171, 96, 1440, 864});
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(1170, 20, &ah);
}
