//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_TEACHERMANAGEMENT_H
#define CPP_SE_TEACHERMANAGEMENT_H
// 图形对象
extern object teacherLessonSearchButton;
extern object teacherProjectSearchButton;
extern object examScoreInputButton;
// bool标志
extern bool teacherLessonSearch_;
extern bool teacherProjectSearch_;
extern bool examScoreInput_;
// string
extern std::string s_teacherId;
// 教师管理
void TeacherManagementGraph(pqxx::connection& conn);
// 教师课程查询
void TeacherLessonSearch(pqxx::connection& conn);
// 教师项目查询
void TeacherProjectSearch(pqxx::connection& conn);
// 考试成绩录入
void ExamScoreInput(pqxx::connection& conn);

#endif //CPP_SE_TEACHERMANAGEMENT_H
