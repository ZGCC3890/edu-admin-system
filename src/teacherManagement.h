//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_TEACHERMANAGEMENT_H
#define CPP_SE_TEACHERMANAGEMENT_H
// ͼ�ζ���
extern object teacherLessonSearchButton;
extern object teacherProjectSearchButton;
extern object examScoreInputButton;
// bool��־
extern bool teacherLessonSearch_;
extern bool teacherProjectSearch_;
extern bool examScoreInput_;
// string
extern std::string s_teacherId;
extern std::string s_teacherName;
extern pqxx::result lessonList;
// ��ʦ����
void TeacherManagementGraph(pqxx::connection& conn);
// ��ý�ʦ���ƺ�ְ�ƺϳɳƺ�
std::string GetTeacherNameTitle(pqxx::connection& conn, std::string teacherId);
// ��ʦ�γ̲�ѯ
void TeacherLessonSearch(pqxx::connection& conn);
// ��ʦ��Ŀ��ѯ
void TeacherProjectSearch(pqxx::connection& conn);
// ���Գɼ�¼��
void ExamScoreInput(pqxx::connection& conn);

#endif //CPP_SE_TEACHERMANAGEMENT_H
