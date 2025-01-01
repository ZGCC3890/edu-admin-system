//
// Created by ZGCC on 24-12-17.
//

#ifndef EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
#define EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
// object
extern object registerButton[10];
extern object scoreInputBar[100];
extern object commitButton;
// string
extern std::string s_userId;
extern std::string s_userIdentity;
extern std::string s_adminId;
extern std::string s_studentScore[100];
// bool
extern bool isTeacher_;
extern bool isStudent_;
extern bool isAdmin_;
// 选择了对应课程的学生列表
extern pqxx::result studentList;
// 考试管理
void ExamManagementGraph(pqxx::connection& conn);
// 判断用户身份
std::string GetUserIdentity(pqxx::connection& conn);
// 教师界面
void IdentityTeacherGraph(pqxx::connection& conn);
// 管理员界面
void IdentityAdminGraph(pqxx::connection& conn);
// 学生界面
void IdentityStudentGraph(pqxx::connection& conn);
// 成绩登记
void ScoresRegister(pqxx::connection& conn, const std::string& s_course_id);
// 更新学生成绩
void UpdateStudentScore(pqxx::connection& conn, std::string session);
#endif //EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
