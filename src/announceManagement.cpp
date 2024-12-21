//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"

void AnnounceManagementGraph(pqxx::connection& conn){
    Menu(2);
    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(2);
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
