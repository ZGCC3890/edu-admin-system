//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"

object teacherLessonSearchButton = {220, 60, 130, 35};
object teacherProjectSearchButton = {teacherLessonSearchButton.posx + teacherLessonSearchButton.width + 30, teacherLessonSearchButton.posy, 130, 30};
object examScoreInputButton = {teacherProjectSearchButton.posx + teacherProjectSearchButton.width + 30, teacherProjectSearchButton.posy, 130, 30};
bool teacherLessonSearch_ = false;
bool teacherProjectSearch_ = false;
bool examScoreInput_ = false;
std::string s_teacherId;
std::string s_teacherName;
pqxx::result lessonList;

void TeacherManagementGraph(pqxx::connection& conn){
    s_teacherId = LoginGraph("teacher", conn, 1);
    if (s_teacherId == " " || s_teacherId == "GraphChanged") return;
    Menu(1);
    ClearWindow(0);
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    fillroundrect_(teacherLessonSearchButton);
    fillroundrect_(teacherProjectSearchButton);
    fillroundrect_(examScoreInputButton);
    OutputText(teacherLessonSearchButton.posx + 5, teacherLessonSearchButton.posy + 8, WHITE, 20, 0, "查询任教课程", "宋体");
    OutputText(teacherProjectSearchButton.posx + 5, teacherProjectSearchButton.posy + 8, WHITE, 20, 0, "查询负责项目", "宋体");
    OutputText(examScoreInputButton.posx + 5, examScoreInputButton.posy + 8, WHITE, 20, 0, "考试成绩录入", "宋体");
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(1);
        ButtonAnimation(msg, teacherLessonSearchButton);
        ButtonAnimation(msg, teacherProjectSearchButton);
        ButtonAnimation(msg, examScoreInputButton);
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    if(isInside(msg, teacherLessonSearchButton)){
                        TeacherLessonSearch(conn);
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
    ClearWindow(95);
    s_teacherName = GetTeacherNameTitle(conn, s_teacherId);
    std::string getLessonSQL = R"(
        SELECT c.course_id, c.course_name, c.classroom, c.schedule,c.current_students, c.max_students
        FROM courses c
        WHERE c.teacher_name = $1
        )";
    pqxx::work txn(conn);
    lessonList = txn.exec_params(getLessonSQL, s_teacherName);
    setfillcolor(WHITE);
    setlinecolor(BLACK);
    rectangle_({220, 105, 140, 30});
    rectangle_({360, 105, 310, 30});
    rectangle_({670, 105, 220, 30});
    rectangle_({890, 105, 170, 30});
    OutputText(220 + 10, 110, BLACK, 20, 0, "课程编号", "宋体");
    OutputText(360 + 10, 110, BLACK, 20, 0, "课程名称", "宋体");
    OutputText(670 + 10, 110, BLACK, 20, 0, "上课时间", "宋体");
    OutputText(890 + 10, 110, BLACK, 20, 0, "上课教室", "宋体");
    for (int i = 0; i < lessonList.size(); ++i) {
        rectangle_({220, 135 + (i % 10) * 30, 140, 30});
        rectangle_({360, 135 + (i % 10) * 30, 310, 30});
        rectangle_({670, 135 + (i % 10) * 30, 220, 30});
        rectangle_({890, 135 + (i % 10) * 30, 170, 30});
        OutputText(220 + 10, 135 + 5 + (i % 10) * 30, BLACK, 20, 0, lessonList[i]["course_id"].as<std::string>().c_str(), "宋体");
        OutputText(360 + 10, 135 + 5 + (i % 10) * 30, BLACK, 20, 0, lessonList[i]["course_name"].as<std::string>().c_str(), "宋体");
        OutputText(670 + 10, 135 + 5 + (i % 10) * 30, BLACK, 20, 0, lessonList[i]["schedule"].as<std::string>().c_str(), "宋体");
        OutputText(890 + 10, 135 + 5 + (i % 10) * 30, BLACK, 20, 0, lessonList[i]["classroom"].as<std::string>().c_str(), "宋体");
        OutputText(995, 135 + 10 + (i % 10) * 30, BLACK, 15, 0, lessonList[i]["current_students"].as<std::string>().c_str(), "宋体");
        OutputText(1015, 135 + 10 + (i % 10) * 30, BLACK, 15, 0, ("| " + lessonList[i]["max_students"].as<std::string>()).c_str(), "宋体");
    }
}

void TeacherProjectSearch(pqxx::connection& conn) {


}

void ExamScoreInput(pqxx::connection& conn) {


}

std::string GetTeacherNameTitle(pqxx::connection& conn, std::string teacherId) {
    std::string name;
    std::string teacherName;
    std::string teacherTitle;
    std::string getTeacherTitleSQL = R"(
        SELECT name, title FROM teachers WHERE teacher_id = $1
        )";
    pqxx::work txn(conn);
    pqxx::result result = txn.exec_params(getTeacherTitleSQL, teacherId);
    teacherName = result[0]["name"].as<std::string>();
    teacherTitle = result[0]["title"].as<std::string>();
    if(teacherTitle == "professor") return ("Prof. " + teacherName);
    else if(teacherTitle == "doctor") return ("Dr. " + teacherName);
    else return teacherName;
}