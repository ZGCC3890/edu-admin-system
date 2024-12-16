//
// Created by ZGCC on 24-12-16.
//
#include "ustil.h"
#include "studentManagement.h"

bool lessonSearchGraph_ = false;
bool lessonSelectGraph_ = false;
bool lessonDropGraph_ = false;

void StudentManagementGraph(pqxx::connection& conn){
    LoginGraph("student", conn);
    Menu(0);
    ClearWindow();
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    object lessonSearchButton = {230, 60, 120, 30};
    fillroundrect_(lessonSearchButton);
    OutputText(lessonSearchButton.posx + 20, lessonSearchButton.posy + 5, WHITE, 20, 0, "查询课程", "宋体");
    object lessonSelectButton = {lessonSearchButton.posx + lessonSearchButton.width + 50, lessonSearchButton.posy, 120, 30};
    fillroundrect_(lessonSelectButton);
    OutputText(lessonSelectButton.posx + 20, lessonSelectButton.posy + 5, WHITE, 20, 0, "选课模块", "宋体");
    object lessonDropButton = {lessonSelectButton.posx + lessonSelectButton.width + 50, lessonSearchButton.posy, 120, 30};
    fillroundrect_(lessonDropButton);
    OutputText(lessonDropButton.posx + 20, lessonDropButton.posy + 5, WHITE, 20, 0, "退课模块", "宋体");
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(0);

        ButtonAnimation(msg, lessonSearchButton, WHITE, CommonBlue);
        ButtonAnimation(msg, lessonSelectButton, WHITE, CommonBlue);
        ButtonAnimation(msg, lessonDropButton, WHITE, CommonBlue);

        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    else if(isInside(msg, lessonSearchButton)){
                        lessonSearchGraph_ = true;
                        lessonSelectGraph_ = false;
                        lessonDropGraph_ = false;
                    }
                    else if(isInside(msg, lessonSelectButton)){
                        lessonSearchGraph_ = false;
                        lessonSelectGraph_ = true;
                        lessonDropGraph_ = false;
                    }
                    else if(isInside(msg, lessonDropButton)){
                        lessonSearchGraph_ = false;
                        lessonSelectGraph_ = false;
                        lessonDropGraph_ = true;
                    }
            }
        }

        if(lessonSearchGraph_) LessonSearchGraph();
        if(lessonSelectGraph_) LessonSelectGraph();
        if(lessonDropGraph_) LessonDropGraph();
    }
}

void LessonSearchGraph() {
    ClearWindow();

}

void LessonSelectGraph() {
    ClearWindow();

}

void LessonDropGraph() {
    ClearWindow();

}