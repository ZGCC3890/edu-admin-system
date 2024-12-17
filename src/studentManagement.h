//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

//��ť����
extern object selectButton[10];     //ѡ�ΰ�ť
extern object dropButton[5];        //�˿ΰ�ť
extern object sCoursePageUpButton;          //��ѡ�α���һҳ
extern object sCoursePageDownButton;        //��ѡ�α���һҳ
extern object aCoursePageUpButton;          //��ѡ�α���һҳ
extern object aCoursePageDownButton;        //��ѡ�α���һҳ
extern object courseSearchButton;           //�γ�ɸѡ��ť
extern object courseResetButton;           //�γ�ɸѡ���ð�ť
extern object courseIdInputBar;             //�γ̱�������
extern object courseNameInputBar;           //�γ����������
extern object courseTeacherNameInputBar;    //�ον�ʦ�����
//bool��־
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
//��ǰҳ�漰��ҳ����
extern int availableCourseCurPage;
extern int selectedCourseCurPage;
extern int availableCourseTotalPage;
extern int selectedCourseTotalPage;
//SQL��ѯ�������
extern pqxx::result selectedCourses;
extern pqxx::result availableCourses;
//ѧ������
void StudentManagementGraph(pqxx::connection& conn);
//��ѯѧ��רҵ
std::string GetStudentMajor(std::string student_id, pqxx::connection& conn);
//���¿γ�����
void SearchLessonData(pqxx::connection& conn);
//���Ʊ��
void DrawCoursesTable();
//���Ʒ�ҳ��ť
void PageButtonDrawing();
//ɸѡ�����
void DrawingFilter();
#endif //CPP_SE_STUDENTMANAGEMENT_H
