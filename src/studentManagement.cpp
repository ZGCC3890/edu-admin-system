//
// Created by ZGCC on 24-12-16.
//
#include "ustil.h"
#include "studentManagement.h"

int availableCourseCurPage = 0;
int selectedCourseCurPage = 0;
int availableCourseTotalPage = 0;
int selectedCourseTotalPage = 0;
object selectButton[10];
object dropButton[5];
object sCoursePageUpButton = {1200, 325, 50, 20};
object sCoursePageDownButton = {1350, 325, 50, 20};
object aCoursePageUpButton = {1200, 745, 50, 20};
object aCoursePageDownButton = {1350, 745, 50, 20};
object courseSearchButton = {990, 55, 100, 30};
object courseResetButton = {1100, 55, 60, 30};
object courseIdInputBar = {230, 55, 140, 30};
object courseNameInputBar = {380, 55, 310, 30};
object courseTeacherNameInputBar = {700, 55, 260, 30};
bool courseId_ = false;
bool courseName_ = false;
bool courseTeacherName_ = false;
bool showSCoursePageButton_ = false;
bool showACoursePageButton_ = false;
std::string s_studentId;
std::string s_courseId;
std::string s_courseName;
std::string s_courseTeacherName;
pqxx::result selectedCourses;
pqxx::result availableCourses;
void StudentManagementGraph(pqxx::connection& conn) {
    s_studentId = LoginGraph("student", conn);
    if (s_studentId == " ") return;
    Menu(0);
    ClearWindow();
    SearchLessonData(conn);
    DrawingFilter();
    while (true) {
        flushmessage(EM_MOUSE);
        //菜单及按钮反馈
        MenuAnimation(0);
        ButtonAnimation(msg, courseSearchButton, WHITE, CommonBlue);
        ButtonAnimation(msg, courseResetButton, WHITE, CommonBlue);
        ButtonAnimation(msg, courseIdInputBar, WHITE, CommonBlue);
        ButtonAnimation(msg, courseNameInputBar, WHITE, CommonBlue);
        ButtonAnimation(msg, courseTeacherNameInputBar, WHITE, CommonBlue);
        //表格绘制
        DrawCoursesTable();
        //翻页按钮绘制
        PageButtonDrawing();
        //退课选课按钮反馈
        for(int i = availableCourseCurPage * 10; i < std::min(availableCourseCurPage * 10 + 10, availableCourses.size()); ++i)
            if(availableCourses[i]["current_students"].as<int>() != availableCourses[i]["max_students"].as<int>())
                ButtonAnimation(msg, selectButton[i % 10], WHITE, CommonBlue);
        for(int i = selectedCourseCurPage * 5; i < std::min(selectedCourseCurPage * 5 + 5, selectedCourses.size()); ++i)
            ButtonAnimation(msg, dropButton[i%5], WHITE, CommonBlue);

        if (courseId_){
            OutputText(courseIdInputBar.posx + 10, courseIdInputBar.posy + 5, BLACK, 20, 0, s_courseId.c_str(), "宋体");
        }else{
            OutputText(courseIdInputBar.posx + 10, courseIdInputBar.posy + 5, RGB(150, 150, 150), 20, 0, "课程编号", "宋体");
        }
        if (courseName_){
            OutputText(courseNameInputBar.posx + 10, courseNameInputBar.posy + 5, BLACK, 20, 0, s_courseName.c_str(), "宋体");
        }else{
            OutputText(courseNameInputBar.posx + 10, courseNameInputBar.posy + 5, RGB(150, 150, 150), 20, 0, "课程名称", "宋体");
        }
        if (courseTeacherName_){
            OutputText(courseTeacherNameInputBar.posx + 10, courseTeacherNameInputBar.posy + 5, BLACK, 20, 0, s_courseTeacherName.c_str(), "宋体");
        }else{
            OutputText(courseTeacherNameInputBar.posx + 10, courseTeacherNameInputBar.posy + 5, RGB(150, 150, 150), 20, 0, "任课教师名称", "宋体");
        }

        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    //如果点击翻页按钮时有多页且当前页数合法,则更新当前页数并清空表格区域
                    if (showSCoursePageButton_ && isInside(msg, sCoursePageUpButton) && selectedCourseCurPage > 0) {
                        --selectedCourseCurPage;
                        setfillcolor(WHITE);
                        setlinecolor(WHITE);
                        fillrectangle_({220, 136, 1190, 180});
                        fillrectangle_({sCoursePageUpButton.posx + 51, sCoursePageUpButton.posy, 90, 30});
                    }
                    else if (showSCoursePageButton_ && isInside(msg, sCoursePageDownButton) && selectedCourseCurPage < selectedCourseTotalPage) {
                        ++selectedCourseCurPage;
                        setfillcolor(WHITE);
                        setlinecolor(WHITE);
                        fillrectangle_({220, 136, 1190, 180});
                        fillrectangle_({sCoursePageUpButton.posx + 51, sCoursePageUpButton.posy, 90, 30});
                    }
                    else if (showACoursePageButton_ && isInside(msg, aCoursePageUpButton) && availableCourseCurPage > 0) {
                        --availableCourseCurPage;
                        setfillcolor(WHITE);
                        setlinecolor(WHITE);
                        fillrectangle_({220, 406, 1190, 330});
                        fillrectangle_({aCoursePageUpButton.posx + 51, aCoursePageUpButton.posy, 90, 30});
                    }
                    else if (showACoursePageButton_ && isInside(msg, aCoursePageDownButton) && availableCourseCurPage < availableCourseTotalPage) {
                        ++availableCourseCurPage;
                        setfillcolor(WHITE);
                        setlinecolor(WHITE);
                        fillrectangle_({220, 406, 1190, 330});
                        fillrectangle_({aCoursePageUpButton.posx + 51, aCoursePageUpButton.posy, 90, 30});
                    }

                    //输入框
                    setfillcolor(WHITE);
                    if (isInside(msg, courseIdInputBar)) {
                        fillroundrect_(courseIdInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "请输入课程编号");
                        courseId_ = true;
                        s_courseId = s;
                    }
                    if (isInside(msg, courseNameInputBar)) {
                        fillroundrect_(courseNameInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "请输入课程名称");
                        courseName_ = true;
                        s_courseName = s;
                    }
                    if (isInside(msg, courseTeacherNameInputBar)) {
                        fillroundrect_(courseTeacherNameInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "请输入任课教师名称");
                        courseTeacherName_ = true;
                        s_courseTeacherName = s;
                    }

                    if (isInside(msg, courseSearchButton)){
                        if(courseId_ || courseName_ || courseTeacherName_){
                            ClearWindow();
                            SearchLessonData(conn);
                        }
                    }

                    if (isInside(msg, courseResetButton)) {
                        courseId_ = false;
                        courseName_ = false;
                        courseTeacherName_ = false;
                        ClearWindow();
                        SearchLessonData(conn);
                        DrawingFilter();
                    }

                    for (int i = availableCourseCurPage * 10; i < std::min(availableCourseCurPage * 10 + 10, availableCourses.size()); ++i) {
                        if (isInside(msg, selectButton[i % 10])) {
                            pqxx::work txn(conn);

                            std::string insertSQL = R"(
                                INSERT INTO enrollments (student_id, course_id, operation)
                                VALUES ($1, $2, 'select')
                                )";
                            // 更新选课课程的人数
                            std::string updateCourseSQL = R"(
                                UPDATE courses
                                SET current_students = current_students + 1
                                WHERE course_id = $1
                                )";

                            txn.exec_params(insertSQL, s_studentId, availableCourses[i]["course_id"].as<std::string>().c_str());
                            txn.exec_params(updateCourseSQL, availableCourses[i]["course_id"].as<std::string>().c_str());
                            txn.commit();
                            //重绘界面
                            ClearWindow();
                            SearchLessonData(conn);
                        }
                    }

                    for (int i = selectedCourseCurPage * 5; i < std::min(selectedCourseCurPage * 5 + 5, selectedCourses.size()); ++i) {
                        if (isInside(msg, dropButton[i % 5])) {
                            pqxx::work txn(conn);

                            std::string insertSQL = R"(
                                INSERT INTO enrollments (student_id, course_id, operation)
                                VALUES ($1, $2, 'drop')
                                )";
                            std::string updateCourseSQL = R"(
                                UPDATE courses
                                SET current_students = current_students - 1
                                WHERE course_id = $1
                                )";

                            txn.exec_params(insertSQL, s_studentId, selectedCourses[i]["course_id"].as<std::string>().c_str());
                            txn.exec_params(updateCourseSQL, selectedCourses[i]["course_id"].as<std::string>().c_str());
                            txn.commit();
                            //重绘界面
                            ClearWindow();
                            SearchLessonData(conn);
                        }
                    }
            }
        }
        Sleep(10);
    }
}

std::string GetStudentMajor(std::string student_id, pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT major FROM students WHERE student_id = $1";
        pqxx::result result = txn.exec_params(sql, student_id);

        if (!result.empty()) {
            return result[0]["major"].c_str();
        } else {
            throw std::runtime_error("Student not found or major not defined.");
        }
    } catch (const std::exception &e) {
        std::cerr << "Error fetching student major: " << e.what() << std::endl;
        return "";
    }
}

void DrawCoursesTable(){
    setlinecolor(BLACK);
    OutputText(220, 110, BLACK, 20, 0, "已选课程列表", "宋体");
    rectangle_({220, 135, 140, 30});
    rectangle_({360, 135, 310, 30});
    rectangle_({670, 135, 260, 30});
    rectangle_({930, 135, 220, 30});
    rectangle_({1150,135, 170, 30});
    OutputText(220 + 10, 140, BLACK, 20, 0, "课程编号", "宋体");
    OutputText(360 + 10, 140, BLACK, 20, 0, "课程名称", "宋体");
    OutputText(670 + 10, 140, BLACK, 20, 0, "任课教师", "宋体");
    OutputText(930 + 10, 140, BLACK, 20, 0, "上课时间", "宋体");
    OutputText(1150 + 10,140, BLACK, 20, 0, "上课教室", "宋体");
    for (int i = selectedCourseCurPage * 5; i < std::min(selectedCourseCurPage * 5 + 5, selectedCourses.size()); ++i) {
        setlinecolor(BLACK);
        rectangle_({220, 165 + (i % 5) * 30, 140, 30});
        rectangle_({360, 165 + (i % 5) * 30, 310, 30});
        rectangle_({670, 165 + (i % 5) * 30, 260, 30});
        rectangle_({930, 165 + (i % 5) * 30, 220, 30});
        rectangle_({1150,165 + (i % 5) * 30, 170, 30});
        OutputText(220 + 10, 165 + 5 + (i % 5) * 30, BLACK, 20, 0, selectedCourses[i]["course_id"].as<std::string>().c_str(), "宋体");
        OutputText(360 + 10, 165 + 5 + (i % 5) * 30, BLACK, 20, 0, selectedCourses[i]["course_name"].as<std::string>().c_str(), "宋体");
        OutputText(670 + 10, 165 + 5 + (i % 5) * 30, BLACK, 20, 0, selectedCourses[i]["teacher_name"].as<std::string>().c_str(), "宋体");
        OutputText(930 + 10, 165 + 5 + (i % 5) * 30, BLACK, 20, 0, selectedCourses[i]["schedule"].as<std::string>().c_str(), "宋体");
        OutputText(1150 + 10,165 + 5 + (i % 5) * 30, BLACK, 20, 0, selectedCourses[i]["classroom"].as<std::string>().c_str(), "宋体");
        dropButton[i % 5] = {1330, 167 + (i % 5) * 30, 80, 25};
        setfillcolor(CommonBlue);
        setlinecolor(CommonBlue);
        fillroundrect_(dropButton[i % 5]);
        OutputText(1330 + 20, 170 + (i % 5) * 30, WHITE, 20, 0, "退课", "宋体");
    }
    setlinecolor(BLACK);
    OutputText(220, 380, BLACK, 20, 0, "可选课程列表", "宋体");
    rectangle_({220, 405, 140, 30});
    rectangle_({360, 405, 310, 30});
    rectangle_({670, 405, 260, 30});
    rectangle_({930, 405, 220, 30});
    rectangle_({1150,405, 170, 30});
    OutputText(220 + 10, 410, BLACK, 20, 0, "课程编号", "宋体");
    OutputText(360 + 10, 410, BLACK, 20, 0, "课程名称", "宋体");
    OutputText(670 + 10, 410, BLACK, 20, 0, "任课教师", "宋体");
    OutputText(930 + 10, 410, BLACK, 20, 0, "上课时间", "宋体");
    OutputText(1150 + 10,410, BLACK, 20, 0, "上课教室", "宋体");
    for (int i = availableCourseCurPage * 10; i < std::min(availableCourseCurPage * 10 + 10, availableCourses.size()); ++i) {
        //可选课程数据
        setlinecolor(BLACK);
        rectangle_({220, 435 + (i % 10) * 30, 140, 30});
        rectangle_({360, 435 + (i % 10) * 30, 310, 30});
        rectangle_({670, 435 + (i % 10) * 30, 260, 30});
        rectangle_({930, 435 + (i % 10) * 30, 220, 30});
        rectangle_({1150,435 + (i % 10) * 30, 170, 30});
        OutputText(220 + 10, 435 + 5 + (i % 10) * 30, BLACK, 20, 0, availableCourses[i]["course_id"].as<std::string>().c_str(), "宋体");
        OutputText(360 + 10, 435 + 5 + (i % 10) * 30, BLACK, 20, 0, availableCourses[i]["course_name"].as<std::string>().c_str(), "宋体");
        OutputText(670 + 10, 435 + 5 + (i % 10) * 30, BLACK, 20, 0, availableCourses[i]["teacher_name"].as<std::string>().c_str(), "宋体");
        OutputText(930 + 10, 435 + 5 + (i % 10) * 30, BLACK, 20, 0, availableCourses[i]["schedule"].as<std::string>().c_str(), "宋体");
        OutputText(1150 + 10,435 + 5 + (i % 10) * 30, BLACK, 20, 0, availableCourses[i]["classroom"].as<std::string>().c_str(), "宋体");
        //选课按钮
        if(availableCourses[i]["current_students"].as<int>() != availableCourses[i]["max_students"].as<int>()) {
            selectButton[i % 10] = {1330, 437 + (i % 10) * 30, 80, 25};
            setfillcolor(CommonBlue);
            setlinecolor(CommonBlue);
            fillroundrect_(selectButton[i % 10]);
            OutputText(1330 + 20, 440 + (i % 10) * 30, WHITE, 20, 0, "选课", "宋体");
        }
        //上课人数
        OutputText(1255, 435 + 10 + (i % 10) * 30, BLACK, 15, 0, availableCourses[i]["current_students"].as<std::string>().c_str(), "宋体");
        OutputText(1275, 435 + 10 + (i % 10) * 30, BLACK, 15, 0, ("| " + availableCourses[i]["max_students"].as<std::string>()).c_str(), "宋体");
    }
}

void SearchLessonData(pqxx::connection& conn){
    // 查询已选课程表
    // 判断逻辑：最后一次对课程的操作是'select'即符合要求
    std::string selectedCoursesSQL = R"(
        SELECT c.course_id, c.course_name, c.teacher_name, c.schedule, c.current_students, c.max_students, c.classroom
        FROM courses c
        JOIN enrollments e ON c.course_id = e.course_id
        WHERE e.student_id = $1
            AND e.enrollment_date = (
                SELECT MAX(e1.enrollment_date)
                FROM enrollments e1
                WHERE e1.student_id = e.student_id
                AND e1.course_id = e.course_id
            )
            AND e.operation = 'select'
        )";
    // 查询可选课程表，级联查询选课记录表enrollments将已选课程排除
    // 判断逻辑：最后一次对课程的操作不是'select'即符合要求
    std::string availableCoursesSQL = R"(
            SELECT c.course_id, c.course_name, c.teacher_name, c.schedule, c.current_students, c.max_students, c.classroom
            FROM courses c
            WHERE (c.major_restriction = 'all' OR c.major_restriction = $2)
                AND NOT EXISTS (
                    SELECT 1
                    FROM enrollments e
                    WHERE e.student_id = $1
                        AND e.course_id = c.course_id
                        AND e.operation = 'select'
                        AND e.enrollment_date = (
                            SELECT MAX(e1.enrollment_date)
                            FROM enrollments e1
                            WHERE e1.student_id = e.student_id
                              AND e1.course_id = e.course_id
                        )
                )
            )";
    if (courseId_){
        selectedCoursesSQL += "AND c.course_id LIKE '%" + s_courseId + "%'";
        availableCoursesSQL += "AND c.course_id LIKE '%" + s_courseId + "%'";
    }
    if (courseName_){
        selectedCoursesSQL += "AND c.course_name LIKE '%" + s_courseName + "%'";
        availableCoursesSQL += "AND c.course_name LIKE '%" + s_courseName + "%'";
    }
    if (courseTeacherName_){
        selectedCoursesSQL += "AND c.teacher_name LIKE '%" + s_courseTeacherName + "%'";
        availableCoursesSQL += "AND c.teacher_name LIKE '%" + s_courseTeacherName + "%'";
    }
    //查询学生专业并获得已选课表和可选课表
    std::string major = GetStudentMajor(s_studentId, conn);
    pqxx::work txn(conn);
    selectedCourses = txn.exec_params(selectedCoursesSQL, s_studentId);
    availableCourses = txn.exec_params(availableCoursesSQL, s_studentId, major);
    //更新课表页数
    selectedCourseCurPage = 0;
    availableCourseCurPage = 0;
    selectedCourseTotalPage = selectedCourses.size() / 5;
    if(selectedCourses.size() % 5 != 0) ++ selectedCourseTotalPage;
    availableCourseTotalPage = availableCourses.size() / 10;
    if(availableCourses.size() % 10 != 0) ++ availableCourseTotalPage;
    //从0开始计数
    --selectedCourseTotalPage;
    --availableCourseTotalPage;
    if(selectedCourseTotalPage > 0) showSCoursePageButton_ = true;
    else showSCoursePageButton_ = false;
    if(availableCourseTotalPage > 0) showACoursePageButton_ = true;
    else showACoursePageButton_ = false;
}

void PageButtonDrawing(){
    if (showSCoursePageButton_){
        setfillcolor(CommonBlue);
        setlinecolor(CommonBlue);
        fillroundrect_(sCoursePageUpButton);
        fillroundrect_(sCoursePageDownButton);
        OutputText(sCoursePageUpButton.posx + 15, sCoursePageUpButton.posy + 3, WHITE, 15, 0, "<=", "宋体");
        OutputText(sCoursePageDownButton.posx + 15, sCoursePageDownButton.posy + 3, WHITE, 15, 0, "=>", "宋体");
        OutputText(sCoursePageUpButton.posx + 70, sCoursePageUpButton.posy + 3, BLACK, 15, 0, std::to_string(selectedCourseCurPage + 1).c_str(), "宋体");
        OutputText(sCoursePageUpButton.posx + 95, sCoursePageUpButton.posy + 3, BLACK, 15, 0, ("|  " + std::to_string(selectedCourseTotalPage + 1)).c_str(), "宋体");
    }

    if (showACoursePageButton_){
        setfillcolor(CommonBlue);
        setlinecolor(CommonBlue);
        fillroundrect_(aCoursePageUpButton);
        fillroundrect_(aCoursePageDownButton);
        OutputText(aCoursePageUpButton.posx + 15, aCoursePageUpButton.posy + 3, WHITE, 15, 0, "<=", "宋体");
        OutputText(aCoursePageDownButton.posx + 15, aCoursePageDownButton.posy + 3, WHITE, 15, 0, "=>", "宋体");
        OutputText(aCoursePageUpButton.posx + 70, aCoursePageUpButton.posy + 3, BLACK, 15, 0, std::to_string(availableCourseCurPage + 1).c_str(), "宋体");
        OutputText(aCoursePageUpButton.posx + 95, aCoursePageUpButton.posy + 3, BLACK, 15, 0, ("|  " + std::to_string(availableCourseTotalPage + 1)).c_str(), "宋体");
    }

}

void DrawingFilter() {
    OutputText(220, 20, BLACK, 20, 0, "课程筛选", "宋体");
    setlinecolor(CommonBlue);
    setfillcolor(CommonBlue);
    fillroundrect_({220, 45, 750, 50});
    fillroundrect_(courseSearchButton);
    fillroundrect_(courseResetButton);
    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillroundrect_(courseIdInputBar);
    fillroundrect_(courseNameInputBar);
    fillroundrect_(courseTeacherNameInputBar);
    OutputText(courseSearchButton.posx + 30, courseSearchButton.posy + 5, WHITE, 20, 0, "筛选", "宋体");
    OutputText(courseResetButton.posx + 10, courseResetButton.posy + 5, WHITE, 20, 0, "重置", "宋体");
}