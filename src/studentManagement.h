//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

// ͼ�ζ���
extern object selectButton[10];     // ѡ�ΰ�ť
extern object dropButton[5];        // �˿ΰ�ť
extern object sCoursePageUpButton;          // ��ѡ�α���һҳ
extern object sCoursePageDownButton;        // ��ѡ�α���һҳ
extern object aCoursePageUpButton;          // ��ѡ�α���һҳ
extern object aCoursePageDownButton;        // ��ѡ�α���һҳ
extern object courseSearchButton;           // �γ�ɸѡ��ť
extern object courseResetButton;            // �γ�ɸѡ���ð�ť
extern object courseIdInputBar;             // �γ̱�������
extern object courseNameInputBar;           // �γ����������
extern object courseTeacherNameInputBar;    // �ον�ʦ�����
// bool��־
extern bool showSCoursePageButton_;         // ��ѡ�η�ҳ��ť��ʾ��־
extern bool showACoursePageButton_;         // ��ѡ�η�ҳ��ť��ʾ��־
extern bool courseId_;                      // course_id���������־
extern bool courseName_;                    // course_nameɸѡ�����־
extern bool courseTeacherName_;             // teacher_nameɸѡ�����־
// string
extern std::string s_studentId;             // student_id�洢�ַ���
extern std::string s_courseId;              // course_id�洢�ַ���
extern std::string s_courseName;            // course_name�洢�ַ���
extern std::string s_courseTeacherName;     // teacher_name�洢�ַ���
// ��ǰҳ�漰��ҳ����
extern int availableCourseCurPage;          // ��ѡ�α�ǰҳ��
extern int selectedCourseCurPage;           // ��ѡ�α�ǰҳ��
extern int availableCourseTotalPage;        // ��ѡ�α���ҳ��
extern int selectedCourseTotalPage;         // ��ѡ�α���ҳ��
// SQL��ѯ�������
extern pqxx::result selectedCourses;        // ��ѡ�α��ѯ���
extern pqxx::result availableCourses;       // ��ѡ�α��ѯ���
// ѧ������
void StudentManagementGraph(pqxx::connection& conn);
// ��ѯѧ��רҵ
std::string GetStudentMajor(const std::string& student_id, pqxx::connection& conn);
// ���¿γ�����
void SearchLessonData(pqxx::connection& conn);
// ���Ʊ��
void DrawCoursesTable();
// ���Ʒ�ҳ��ť
void PageButtonDrawing();
// ɸѡ�����
void DrawingFilter();
#endif //CPP_SE_STUDENTMANAGEMENT_H
