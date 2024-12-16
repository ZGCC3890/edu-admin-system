//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"
#include "teacherManagement.h"

void teacherManagementGraph(){
    Menu(1);
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
