//
// Created by ZGCC on 24-12-17.
//

#include "ustil.h"

void ExamManagementGraph(pqxx::connection& conn){
    Menu(4);
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
