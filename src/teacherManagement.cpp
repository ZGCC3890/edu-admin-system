//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"

object teacherLessonSearchButton;
object teacherProjectSearchButton;
object examScoreInputButton;
bool teacherLessonSearch_ = false;
bool teacherProjectSearch_ = false;
bool examScoreInput_ = false;
std::string s_teacherId;

void TeacherManagementGraph(pqxx::connection& conn){
    s_teacherId = LoginGraph("teacher", conn, 1);
    if (s_teacherId == " " || s_teacherId == "GraphChanged") return;
    Menu(1);
    ClearWindow(0);
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    fillrectangle_(teacherLessonSearchButton);
    fillrectangle_(teacherProjectSearchButton);
    fillrectangle_(examScoreInputButton);
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(1);
        ButtonAnimation(msg, teacherLessonSearchButton);
        ButtonAnimation(msg, teacherProjectSearchButton);
        ButtonAnimation(msg, examScoreInputButton);
        if (teacherLessonSearch_) TeacherLessonSearch(conn);
        if (teacherProjectSearch_) TeacherProjectSearch(conn);
        if (examScoreInput_) ExamScoreInput(conn);
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    if(isInside(msg, teacherLessonSearchButton)){
                        teacherLessonSearch_ = true;
                        teacherProjectSearch_ = false;
                        examScoreInput_ = false;
                    }
                    if(isInside(msg, teacherProjectSearchButton)){
                        teacherLessonSearch_ = false;
                        teacherProjectSearch_ = true;
                        examScoreInput_ = false;
                    }
                    if(isInside(msg, examScoreInputButton)){
                        teacherLessonSearch_ = false;
                        teacherProjectSearch_ = false;
                        examScoreInput_ = true;
                    }
            }
        }
    }
}

void TeacherLessonSearch(pqxx::connection& conn) {


    if (peekmessage(&msg, EM_MOUSE)) {
        switch (msg.message) {
            case WM_LBUTTONDOWN:

        }
    }
}

void TeacherProjectSearch(pqxx::connection& conn) {


    if (peekmessage(&msg, EM_MOUSE)) {
        switch (msg.message) {
            case WM_LBUTTONDOWN:

        }
    }
}

void ExamScoreInput(pqxx::connection& conn) {


    if (peekmessage(&msg, EM_MOUSE)) {
        switch (msg.message) {
            case WM_LBUTTONDOWN:

        }
    }
}