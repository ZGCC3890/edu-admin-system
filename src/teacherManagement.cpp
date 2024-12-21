//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"

std::string s_teacherId;

void TeacherManagementGraph(pqxx::connection& conn){
    s_teacherId = LoginGraph("teacher", conn);
    if (s_teacherId == " ") return;
    Menu(1);
    ClearWindow();
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(1);
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    break;
            }
        }
    }
}
