//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_TEACHERMANAGEMENT_H
#define CPP_SE_TEACHERMANAGEMENT_H
// 图形对象
extern object teacherLessonSearchButton;
extern object teacherProjectSearchButton;
extern object teacherStudentProjectSearchButton;
extern object examScoreInputButton;
// bool标志
extern bool teacherLessonSearch_;
extern bool teacherProjectSearch_;
extern bool teacherStudentProjectSearch_;
extern bool examScoreInput_;
// string
extern std::string s_teacherId;
extern std::string s_teacherName;
// result结构
extern pqxx::result lessonList;
extern pqxx::result projectList;
// 教师管理
void TeacherManagementGraph(pqxx::connection& conn);
// 获得教师名称和职称合成称呼
std::string GetTeacherNameTitle(pqxx::connection& conn, std::string teacherId);
// 教师课程查询
void TeacherLessonSearch(pqxx::connection& conn);
// 教师项目查询
void TeacherProjectSearch(pqxx::connection& conn);
// 考试成绩录入
void ExamScoreInput(pqxx::connection& conn);
// 共研项目查询
void TeacherStudentProjectSearch(pqxx::connection& conn);

#endif //CPP_SE_TEACHERMANAGEMENT_H
