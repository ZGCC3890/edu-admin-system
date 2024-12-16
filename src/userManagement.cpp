//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"
#include "userManagement.h"

void UserManagementGraph(pqxx::connection& conn){
    Menu(3);
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(3);
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