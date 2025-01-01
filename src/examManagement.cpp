//
// Created by ZGCC on 24-12-17.
//

#include "ustil.h"

std::string s_userId;
std::string s_userIdentity;
std::string s_adminId;
std::string s_studentScore[100];
bool isTeacher_ = false;
bool isStudent_ = false;
bool isAdmin_ = false;
object registerButton[10];
object scoreInputBar[100];
object commitButton = {1160, 320,  80, 30};
pqxx::result studentList;
void ExamManagementGraph(pqxx::connection& conn){
    s_userId = LoginGraph("user", conn, 4);
    if (s_userId == " " || s_userId == "GraphChanged") return;
    s_userIdentity = GetUserIdentity(conn);
    Menu(4);
    ClearWindow(0);
    if(s_userIdentity == "admin") {
        isAdmin_ = true;
        isTeacher_ = false;
        isStudent_ = false;
        IdentityAdminGraph(conn);
    }
    else if(s_userIdentity == "teacher") {
        isAdmin_ = false;
        isTeacher_ = true;
        isStudent_ = false;
        IdentityTeacherGraph(conn);
    }
    else if(s_userIdentity == "student") {
        isAdmin_ = false;
        isTeacher_ = false;
        isStudent_ = true;
        IdentityStudentGraph(conn);
    }
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(4);
        // 教师功能响应
        if(isTeacher_){
            if(studentList.size() > 0)
                ButtonAnimation(msg, commitButton);
            for (int i = 0; i < std::min(5, lessonList.size()); ++i) {
                ButtonAnimation(msg, registerButton[i]);
            }

            for (int i = 0; i < studentList.size(); ++i) {
                ButtonAnimation(msg, scoreInputBar[i], CommonBlue, BLACK, 1, "rectangle");
            }
        }
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    // 教师功能响应
                    if(isTeacher_){
                        if(isInside(msg, commitButton)){
                            char s[100] = " ";
                            InputBox(s, 100, "请输入学期(20xx-x)：");
                            std::string session = s;
                            if(session.size() < 4) session = "1970-1";
                            UpdateStudentScore(conn, session);
                        }
                        for (int i = 0; i < std::min(5, lessonList.size()); ++i) {
                            if(isInside(msg, registerButton[i])){
                                s_courseId = lessonList[i]["course_id"].as<std::string>();
                                s_courseName = lessonList[i]["course_name"].as<std::string>();
                                ScoresRegister(conn, s_courseId);
                            }
                        }
                        for (int i = 0; i < studentList.size(); ++i) {
                            if(isInside(msg, scoreInputBar[i])){
                                setlinecolor(BLACK);
                                setfillcolor(WHITE);
                                fillrectangle_(scoreInputBar[i]);
                                char s[100] = " ";
                                std::string tmp = "请输入" + studentList[i]["name"].as<std::string>() + "的成绩：";
                                InputBox(s, 100, tmp.c_str());
                                tmp = s;
                                if(stod(tmp) >= 0 && stod(tmp) <= 100) {
                                    s_studentScore[i] = s;
                                    OutputText(scoreInputBar[i].posx + 30, scoreInputBar[i].posy + 5, BLACK,
                                               s_studentScore[i].c_str());
                                }else{
                                    HWND er = GetHWnd();
                                    MessageBox(er, "成绩无效，请输入0-100的数字", "错误", MB_OK);
                                    s_studentScore[i].clear();
                                }
                            }
                        }
                    }
            }
        }
    }
}

std::string GetUserIdentity(pqxx::connection& conn){
    pqxx::result res;
    std::string sql = "SELECT identity FROM users WHERE user_id = $1 AND password = $2";
    pqxx::work txn(conn);
    res = txn.exec_params(sql, s_userId, s_userPassword);
    return res[0][0].as<std::string>();
}

void IdentityTeacherGraph(pqxx::connection& conn){
    ClearWindow(0);
    s_teacherId = s_userId;
    GetLessonList(conn);
    setfillcolor(WHITE);
    setlinecolor(BLACK);
    rectangle_({220, 105, 140, 30});
    rectangle_({360, 105, 310, 30});
    rectangle_({670, 105, 220, 30});
    rectangle_({890, 105, 170, 30});
    OutputText(220 + 10, 110, BLACK, "课程编号");
    OutputText(360 + 10, 110, BLACK, "课程名称");
    OutputText(670 + 10, 110, BLACK, "上课时间");
    OutputText(890 + 10, 110, BLACK, "上课教室");
    for (int i = 0; i < std::min(lessonList.size(), 5); ++i) {
        setfillcolor(BLACK);
        setlinecolor(BLACK);
        rectangle_({220, 135 + (i % 5) * 30, 140, 30});
        rectangle_({360, 135 + (i % 5) * 30, 310, 30});
        rectangle_({670, 135 + (i % 5) * 30, 220, 30});
        rectangle_({890, 135 + (i % 5) * 30, 170, 30});
        OutputText(220 + 10, 135 + 5 + (i % 5) * 30, BLACK, lessonList[i]["course_id"].as<std::string>().c_str());
        OutputText(360 + 10, 135 + 5 + (i % 5) * 30, BLACK, lessonList[i]["course_name"].as<std::string>().c_str());
        OutputText(670 + 10, 135 + 5 + (i % 5) * 30, BLACK, lessonList[i]["schedule"].as<std::string>().c_str());
        OutputText(890 + 10, 135 + 5 + (i % 5) * 30, BLACK, lessonList[i]["classroom"].as<std::string>().c_str());
        OutputText(995, 135 + 10 + (i % 5) * 30, BLACK, lessonList[i]["current_students"].as<std::string>().c_str(), 15);
        OutputText(1015, 135 + 10 + (i % 5) * 30, BLACK, ("| " + lessonList[i]["max_students"].as<std::string>()).c_str(), 15);
        registerButton[i % 5] = {1070, 137 + (i % 5) * 30, 80, 25};
        setfillcolor(CommonBlue);
        setlinecolor(CommonBlue);
        fillroundrect_(registerButton[i%5]);
        OutputText(1070 + 20, 140 + (i % 5) * 30, WHITE, "登记");
    }
}

void IdentityStudentGraph(pqxx::connection& conn){
    ClearWindow(0);
    s_studentId = s_userId;
}

void IdentityAdminGraph(pqxx::connection& conn){
    ClearWindow(0);
    s_adminId = s_userId;

}

void ScoresRegister(pqxx::connection& conn, const std::string& s_course_id){
    ClearWindow(320);
    std::string getStudentListSQL = R"(
        SELECT e.student_id, s.name, COALESCE(sc.grade, 0) AS grade
        FROM enrollments e
        JOIN students s ON e.student_id = s.student_id
        LEFT JOIN scores sc ON e.student_id = sc.student_id AND e.course_id = sc.course_id
        WHERE e.course_id = $1
            AND e.operation = 'select'
            AND e.enrollment_date = (
                SELECT MAX(e1.enrollment_date)
                FROM enrollments e1
                WHERE e1.student_id = e.student_id
                    AND e1.course_id = e.course_id
            );
    )";
    pqxx::work txn(conn);
    studentList = txn.exec_params(getStudentListSQL, s_course_id);
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    fillroundrect_(commitButton);
    OutputText(commitButton.posx + 20, commitButton.posy + 5, WHITE, "提交");
    setfillcolor(WHITE);
    setlinecolor(BLACK);
    rectangle_({220, 320, 140, 30});
    rectangle_({360, 320, 180, 30});
    rectangle_({540, 320, 140, 30});
    OutputText(220 + 10, 320 + 5, BLACK, "学号");
    OutputText(360 + 10, 320 + 5, BLACK, "姓名");
    OutputText(540 + 10, 320 + 5, BLACK, "成绩");
    for (int i = 0; i < studentList.size(); ++i) {
        setfillcolor(WHITE);
        setlinecolor(BLACK);
        rectangle_({220, 350 + (i % 15) * 30, 140, 30});
        rectangle_({360, 350 + (i % 15) * 30, 180, 30});
        scoreInputBar[i] = {540, 350 + (i % 15) * 30, 140, 30};
        rectangle_(scoreInputBar[i]);
        OutputText(220 + 10, 350 + 5 + (i % 15) * 30, BLACK, studentList[i]["student_id"].as<std::string>().c_str());
        OutputText(360 + 10, 350 + 5 + (i % 15) * 30, BLACK, studentList[i]["name"].as<std::string>().c_str());
        OutputText(540 + 10, 350 + 5 + (i % 15) * 30, BLACK, studentList[i]["grade"].as<std::string>().c_str());
    }
}

void UpdateStudentScore(pqxx::connection& conn, std::string session){
    for (int i = 0; i < studentList.size(); ++i) {
        if(!s_studentScore[i].empty()){
            std::string commitScoreSQL = R"(
                MERGE INTO scores AS target
                USING (
                    SELECT $1 AS student_id, $2 AS exam_name, $3 AS grade, $4 AS session, $5 AS teacher_id, $6 AS course_id
                ) AS source
                ON (target.student_id = source.student_id AND target.exam_name = source.exam_name AND target.session = source.session)
                WHEN MATCHED THEN
                    UPDATE SET grade = source.grade,
                                teacher_id = source.teacher_id
                WHEN NOT MATCHED THEN
                    INSERT (student_id, exam_name, grade, session, teacher_id, course_id)
                    VALUES (source.student_id, source.exam_name, source.grade, source.session, source.teacher_id, source.course_id);
            )";
            pqxx::work txn(conn);
            txn.exec_params(commitScoreSQL, studentList[i]["student_id"].as<std::string>(), s_courseName, s_studentScore[i], session, s_teacherId, s_courseId);
            txn.commit();
        }
    }
}