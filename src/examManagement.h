//
// Created by ZGCC on 24-12-17.
//

#ifndef EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
#define EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
// string
extern std::string s_userId;
extern std::string s_userIdentity;
// bool
extern bool isTeacher_;
extern bool isStudent_;
extern bool isAdmin_;

// 考试管理
void ExamManagementGraph(pqxx::connection& conn);
// 判断用户身份
std::string GetUserIdentity(pqxx::connection& conn);
#endif //EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
