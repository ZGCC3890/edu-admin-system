#include "ustil.h"
#include "graphFunctions.h"
#include "studentManagement.h"
#include "teacherManagement.h"
#include "announceManagement.h"
#include "userManagement.h"

using namespace std;

ExMessage msg;
MENU curGraph = MENU::STUDENT_MGMT;

int main() {
    //建立连接
    pair<string, string> con = EstablishConnection("config.txt");
    pqxx::connection localConnection(con.first);
    pqxx::connection cloudConnection(con.second);

    //初始化窗口
    initgraph(1440, 864 | EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();

    //绘制校徽
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(1150, 20, &ah);

    while(true){
        switch (curGraph) {
            case MENU::STUDENT_MGMT:
                studentManagementGraph();
                break;
            case MENU::TEACHER_MGMT:
                teacherManagementGraph();
                break;
            case MENU::ANNOUNCE_MGMT:
                announceManagementGraph();
                break;
            case MENU::USER_MGMT:
                userManagementGraph();
                break;
            case MENU::END:
                closegraph();
                return 0;
        }
    }
}

string LoadConfig(){
    string line, options;
    getline(cin, line);
    options = line.substr(line.find('=') + 1);
    return options;
}

pair<string, string> EstablishConnection(const string& filename) {
    if (!freopen(filename.c_str(), "r", stdin)) {
        throw runtime_error("无法打开配置文件: " + filename);
    }

    string optionLocal = LoadConfig();
    string optionCloud = LoadConfig();

    freopen("CON", "r", stdin);
    return {optionLocal, optionCloud};
}

void Menu(int n) {
    setlinecolor(CommonBlue);
    setfillcolor(CommonBlue);
    object menuBase = {0, 0, 170, 1080};
    fillrectangle_(menuBase);
    setfillcolor(LightBlue);
    object menuSelect = {0, 60 + n * 100, 170, 100};
    fillrectangle_(menuSelect);
}

MENU MenuChoose() {
    if(msg.x >= 0 && msg.x <= 170){
        if(msg.y >= 60 && msg.y <= 160) return MENU::STUDENT_MGMT;
        else if(msg.y >= 160 && msg.y <= 260) return MENU::TEACHER_MGMT;
        else if(msg.y >= 260 && msg.y <= 360) return MENU::ANNOUNCE_MGMT;
        else if(msg.y >= 360 && msg.y <= 460) return MENU::USER_MGMT;
    }
    return curGraph;
}