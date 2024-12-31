//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

// 图形对象
extern object selectButton[10];     // 选课按钮
extern object dropButton[5];        // 退课按钮
extern object sCoursePageUpButton;          // 已选课表上一页
extern object sCoursePageDownButton;        // 已选课表下一页
extern object aCoursePageUpButton;          // 可选课表上一页
extern object aCoursePageDownButton;        // 可选课表下一页
extern object courseSearchButton;           // 课程筛选按钮
extern object courseResetButton;            // 课程筛选重置按钮
extern object courseIdInputBar;             // 课程编号输入框
extern object courseNameInputBar;           // 课程名称输入框
extern object courseTeacherNameInputBar;    // 任课教师输入框
// bool标志
extern bool showSCoursePageButton_;         // 已选课翻页按钮显示标志
extern bool showACoursePageButton_;         // 可选课翻页按钮显示标志
extern bool courseId_;                      // course_id搜索输入标志
extern bool courseName_;                    // course_name筛选输入标志
extern bool courseTeacherName_;             // teacher_name筛选输入标志
// string
extern std::string s_studentId;             // student_id存储字符串
extern std::string s_courseId;              // course_id存储字符串
extern std::string s_courseName;            // course_name存储字符串
extern std::string s_courseTeacherName;     // teacher_name存储字符串
// 当前页面及总页面数
extern int availableCourseCurPage;          // 可选课表当前页面
extern int selectedCourseCurPage;           // 已选课表当前页面
extern int availableCourseTotalPage;        // 可选课表总页数
extern int selectedCourseTotalPage;         // 已选课表总页数
// SQL查询结果对象
extern pqxx::result selectedCourses;        // 已选课表查询结果
extern pqxx::result availableCourses;       // 可选课表查询结果
// 学生管理
void StudentManagementGraph(pqxx::connection& conn);
// 查询学生专业
std::string GetStudentMajor(const std::string& student_id, pqxx::connection& conn);
// 更新课程数据
void SearchLessonData(pqxx::connection& conn);
// 绘制表格
void DrawCoursesTable();
// 绘制翻页按钮
void PageButtonDrawing();
// 筛选框绘制
void DrawingFilter();
#endif //CPP_SE_STUDENTMANAGEMENT_H
