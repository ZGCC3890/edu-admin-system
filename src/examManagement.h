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
// ѡ���˶�Ӧ�γ̵�ѧ���б�
extern pqxx::result studentList;
// ���Թ���
void ExamManagementGraph(pqxx::connection& conn);
// �ж��û����
std::string GetUserIdentity(pqxx::connection& conn);
// ��ʦ����
void IdentityTeacherGraph(pqxx::connection& conn);
// ����Ա����
void IdentityAdminGraph(pqxx::connection& conn);
// ѧ������
void IdentityStudentGraph(pqxx::connection& conn);
// �ɼ��Ǽ�
void ScoresRegister(pqxx::connection& conn, const std::string& s_course_id);
// ����ѧ���ɼ�
void UpdateStudentScore(pqxx::connection& conn, std::string session);
#endif //EDU_ADMIN_SYSTEM_EXAMMANAGEMENT_H
