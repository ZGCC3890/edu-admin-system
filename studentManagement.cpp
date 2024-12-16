//
// Created by ZGCC on 24-12-16.
//
#include "ustil.h"
#include "studentManagement.h"

void studentManagementGraph(){
    Menu(0);
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(0);
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
