//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

extern object lessonSearchButton;
extern object lessonSelectButton;
extern object lessonDropButton;
extern bool lessonSearchGraph_;
extern bool lessonSelectGraph_;
extern bool lessonDropGraph_;

//学生管理
void StudentManagementGraph(pqxx::connection& conn);
//课程查询
void LessonSearchGraph();
//选课
void LessonSelectGraph();
//退课
void LessonDropGraph();

#endif //CPP_SE_STUDENTMANAGEMENT_H
