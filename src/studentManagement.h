//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

//按钮对象
extern object selectButton[10];     //选课按钮
extern object dropButton[5];        //退课按钮
extern object sCoursePageUpButton;      //已选课表上一页
extern object sCoursePageDownButton;    //已选课表下一页
extern object aCoursePageUpButton;      //可选课表上一页
extern object aCoursePageDownButton;    //可选课表下一页
//bool标志
extern bool showSCoursePageButton_;
extern bool showACoursePageButton_;
//当前页面及总页面数
extern int availableCourseCurPage;
extern int selectedCourseCurPage;
extern int availableCourseTotalPage;
extern int selectedCourseTotalPage;
//学生id
extern std::string s_studentId;
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
#endif //CPP_SE_STUDENTMANAGEMENT_H
