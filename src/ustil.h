//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_USTIL_H
#define CPP_SE_USTIL_H
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>
#include "graphFunctions.h"
#include "studentManagement.h"
#include "teacherManagement.h"
#include "announceManagement.h"
#include "userManagement.h"

#define CommonBlue RGB(50, 100, 200)
#define LightBlue RGB(70, 120, 210)

//����ö����
enum class MENU{
    STUDENT_MGMT,
    TEACHER_MGMT,
    ANNOUNCE_MGMT,
    USER_MGMT,
    END
};

//�����Ϣ�ṹ��
extern ExMessage msg;

//��ǰ����
extern MENU curGraph;

//sql��ѯ���
extern pqxx::result res;

//��ȡconfig
std::string LoadConfig();
//��config�ļ���ȡ���ã���������
std::pair<std::string, std::string> EstablishConnection(const std::string& filename);

//���Ʋ˵�
void Menu(int n);
//�˵�ѡ��
MENU MenuChoose();

//�û�������־
extern bool userName_;
extern std::string s_userName;
//�û����뼰��־
extern bool userPassword_;
extern std::string s_userPassword;
//��¼���
bool LoginCheck(const char* identity, pqxx::connection& conn);
//��¼����
std::string LoginGraph(const char* identity, pqxx::connection& conn);

#endif //CPP_SE_USTIL_H
