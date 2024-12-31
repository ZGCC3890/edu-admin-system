//
// Created by ZGCC on 24-12-17.
//

#include "ustil.h"

//object teacherLessonSearchButton = {220, 60, 130, 35};
std::string s_userId;
std::string s_userIdentity;
bool isTeacher_ = false;
bool isStudent_ = false;
bool isAdmin_ = false;
void ExamManagementGraph(pqxx::connection& conn){
    s_userId = LoginGraph("user", conn, 4);
    if (s_userId == " " || s_userId == "GraphChanged") return;
    s_userIdentity = GetUserIdentity(conn);
    if(s_userIdentity == "admin") {
        isAdmin_ = true;
        isTeacher_ = false;
        isStudent_ = false;
    }
    else if(s_userIdentity == "teacher") {
        isAdmin_ = false;
        isTeacher_ = true;
        isStudent_ = false;
    }
    else if(s_userIdentity == "student") {
        isAdmin_ = false;
        isTeacher_ = false;
        isStudent_ = true;
    }

    Menu(4);
    ClearWindow(0);
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(4);
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
            }
        }
    }
}

std::string GetUserIdentity(pqxx::connection& conn){
    pqxx::result res;
    std::string sql = "SELECT identity FROM users WHERE user_id = $1 AND password = $2";
    pqxx::work txn(conn);
    res = txn.exec_params(sql, s_userId, s_userPassword);
    return res[0][0].as<std::string>();
}