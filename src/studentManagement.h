//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_STUDENTMANAGEMENT_H
#define CPP_SE_STUDENTMANAGEMENT_H

//��ť����
extern object selectButton[10];     //ѡ�ΰ�ť
extern object dropButton[5];        //�˿ΰ�ť
extern object sCoursePageUpButton;      //��ѡ�α���һҳ
extern object sCoursePageDownButton;    //��ѡ�α���һҳ
extern object aCoursePageUpButton;      //��ѡ�α���һҳ
extern object aCoursePageDownButton;    //��ѡ�α���һҳ
//bool��־
extern bool showSCoursePageButton_;
extern bool showACoursePageButton_;
//��ǰҳ�漰��ҳ����
extern int availableCourseCurPage;
extern int selectedCourseCurPage;
extern int availableCourseTotalPage;
extern int selectedCourseTotalPage;
//ѧ��id
extern std::string s_studentId;
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
#endif //CPP_SE_STUDENTMANAGEMENT_H
