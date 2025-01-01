#include "ustil.h"

using namespace std;

ExMessage msg;
MENU curGraph = MENU::STUDENT_MGMT;

int main() {
    // 建立连接
    pair<string, string> con = EstablishConnection("../config.txt");
    pqxx::connection localConnection(con.first);
    pqxx::connection cloudConnection(con.second);

    // 初始化窗口
    initgraph(1440, 864 | EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();

    // 绘制校徽
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(1170, 20, &ah);

    while(true){
        switch (curGraph) {
            case MENU::STUDENT_MGMT:
                StudentManagementGraph(localConnection);
                break;
            case MENU::TEACHER_MGMT:
                TeacherManagementGraph(localConnection);
                break;
            case MENU::ANNOUNCE_MGMT:
                AnnouncementManagementGraph(localConnection);
                break;
            case MENU::USER_MGMT:
                UserManagementGraph(localConnection);
                break;
            case MENU::EXAM_MGMT:
                ExamManagementGraph(localConnection);
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
    if(n == 0)
        OutputText(25, 100, YELLOW, "学生选课模块");
    else OutputText(25, 100, WHITE, "学生选课模块");
    if(n == 1)
        OutputText(25, 200, YELLOW, "教师管理模块");
    else OutputText(25, 200, WHITE, "教师管理模块");
    if(n == 2)
        OutputText(25, 300, YELLOW, "公告管理模块");
    else OutputText(25, 300, WHITE, "公告管理模块");
    if(n == 3)
        OutputText(25, 400, YELLOW, "用户管理模块");
    else OutputText(25, 400, WHITE, "用户管理模块");
    if(n == 4)
        OutputText(25, 500, YELLOW, "考试管理模块");
    else OutputText(25, 500, WHITE, "考试管理模块");
    OutputText(65, 800, WHITE, "退出");
}

MENU MenuChoose() {
    if(msg.x >= 0 && msg.x <= 170){
        if(msg.y >= 60 && msg.y <= 160) return MENU::STUDENT_MGMT;
        else if(msg.y >= 160 && msg.y <= 260) return MENU::TEACHER_MGMT;
        else if(msg.y >= 260 && msg.y <= 360) return MENU::ANNOUNCE_MGMT;
        else if(msg.y >= 360 && msg.y <= 460) return MENU::USER_MGMT;
        else if(msg.y >= 460 && msg.y <= 560) return MENU::EXAM_MGMT;
        else if(msg.y >= 760 && msg.y <= 860) return MENU::END;
    }
    return curGraph;
}

bool userName_ = false;
bool userPassword_ = false;
string s_userName;
string s_userPassword;
bool LoginCheck(const std::string& identity, pqxx::connection& conn){
    pqxx::work txn(conn);
    pqxx::result result;
    // 参数化 SQL 查询
    if(identity == "user"){
        string sql = "SELECT COUNT(*) FROM users WHERE user_id = $1 AND password = $2";
        result = txn.exec_params(sql, s_userName, s_userPassword);
    }
    else {
        string sql = "SELECT COUNT(*) FROM users WHERE user_id = $1 AND password = $2 AND identity = $3";
        result = txn.exec_params(sql, s_userName, s_userPassword, identity);
    }

    // 检查结果并解析
    if (!result.empty()) {
        int count = result[0][0].as<int>();
        return count > 0; // 如果 count > 0，说明用户存在
    }
    return false;
}
std::string LoginGraph(const char* identity, pqxx::connection& conn, int menu) {
    Menu(menu);
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    fillrectangle_({220, 0, 1440, 864});
    ClearWindow(0);
    object userNameInputBar = {680, 300, 220, 40};
    object userPasswordInputBar = {680, 300 + 60, 220, 40};
    object loginButton = {730, 360 + 60, 120, 35};
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    fillroundrect_(loginButton);
    setfillcolor(WHITE);
    setlinecolor(BLACK);
    fillroundrect_(userNameInputBar);
    fillroundrect_(userPasswordInputBar);
    OutputText(loginButton.posx + 35, loginButton.posy + 8, WHITE, "登录");

    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(-2);

        ButtonAnimation(msg, userNameInputBar, BLACK, LIGHTGRAY, 1);
        ButtonAnimation(msg, userPasswordInputBar, BLACK, LIGHTGRAY, 1);
        ButtonAnimation(msg, loginButton);

        if(userName_) OutputText(userNameInputBar.posx + 10, userNameInputBar.posy + 10, BLACK, s_userName.c_str(), 22);
        else OutputText(userNameInputBar.posx + 10, userNameInputBar.posy + 8, RGB(150, 150, 150), "请输入用户id", 22);

        if(userPassword_) OutputText(userPasswordInputBar.posx + 10, userPasswordInputBar.posy + 10, BLACK, s_userPassword.c_str(), 22);
        else OutputText(userPasswordInputBar.posx + 10, userPasswordInputBar.posy + 8, RGB(150, 150, 150), "请输入用户密码", 22);

        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        if(curGraph == MENU::END) return " ";
                        return "GraphChanged";
                    }
                    if (isInside(msg, userNameInputBar)){
                        fillroundrect_(userNameInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "请输入用户id");
                        userName_ = true;
                        s_userName = s;
                    }
                    else if (isInside(msg, userPasswordInputBar)){
                        fillroundrect_(userPasswordInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "请输入用户密码");
                        userPassword_ = true;
                        s_userPassword = s;
                    }
                    else if(isInside(msg, loginButton)){
                        if(userName_ && userPassword_ && LoginCheck(identity, conn)){
                            return s_userName;
                        }
                        else{
                            HWND er = GetHWnd();
                            MessageBox(er, "用户名或密码错误", "错误", MB_OK);
                        }
                    }
            }
        }
    }
}