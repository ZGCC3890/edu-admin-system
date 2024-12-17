//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

//按钮对象
extern object selectButton[10];     //选课按钮
extern object dropButton[5];        //退课按钮
extern object sCoursePageUpButton;          //已选课表上一页
extern object sCoursePageDownButton;        //已选课表下一页
extern object aCoursePageUpButton;          //可选课表上一页
extern object aCoursePageDownButton;        //可选课表下一页
extern object courseSearchButton;           //课程筛选按钮
extern object courseResetButton;           //课程筛选重置按钮
extern object courseIdInputBar;             //课程编号输入框
extern object courseNameInputBar;           //课程名称输入框
extern object courseTeacherNameInputBar;    //任课教师输入框
//bool标志
extern bool showSCoursePageButton_;
extern bool showACoursePageButton_;
extern bool courseId_;
extern bool courseName_;
extern bool courseTeacherName_;
//string
extern std::string s_studentId;
extern std::string s_courseId;
extern std::string s_courseName;
extern std::string s_courseTeacherName;
//当前页面及总页面数
extern int availableCourseCurPage;
extern int selectedCourseCurPage;
extern int availableCourseTotalPage;
extern int selectedCourseTotalPage;
//SQL查询结果对象
extern pqxx::result selectedCourses;
extern pqxx::result availableCourses;
//学生管理
void StudentManagementGraph(pqxx::connection& conn);
//查询学生专业
std::string GetStudentMajor(std::string student_id, pqxx::connection& conn);
//更新课程数据
void SearchLessonData(pqxx::connection& conn);
//绘制表格
void DrawCoursesTable();
//绘制翻页按钮
void PageButtonDrawing();
//筛选框绘制
void DrawingFilter();
#endif //CPP_SE_STUDENTMANAGEMENT_H
