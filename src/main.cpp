#include "ustil.h"

using namespace std;

ExMessage msg;
MENU curGraph = MENU::STUDENT_MGMT;

int main() {
    //��������
    pair<string, string> con = EstablishConnection("../config.txt");
    pqxx::connection localConnection(con.first);
    pqxx::connection cloudConnection(con.second);

    //��ʼ������
    initgraph(1440, 864 | EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();

    //����У��
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
                AnnounceManagementGraph(localConnection);
                break;
            case MENU::USER_MGMT:
                UserManagementGraph(localConnection);
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
        throw runtime_error("�޷��������ļ�: " + filename);
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
        OutputText(25, 100, YELLOW, 20, 0, "ѧ��ѡ��ģ��", "����");
    else OutputText(25, 100, WHITE, 20, 0, "ѧ��ѡ��ģ��", "����");
    if(n == 1)
        OutputText(25, 200, YELLOW, 20, 0, "��ʦ����ģ��", "����");
    else OutputText(25, 200, WHITE, 20, 0, "��ʦ����ģ��", "����");
    if(n == 2)
        OutputText(25, 300, YELLOW, 20, 0, "�������ģ��", "����");
    else OutputText(25, 300, WHITE, 20, 0, "�������ģ��", "����");
    if(n == 3)
        OutputText(25, 400, YELLOW, 20, 0, "�û�����ģ��", "����");
    else OutputText(25, 400, WHITE, 20, 0, "�û�����ģ��", "����");
    OutputText(65, 800, WHITE, 20, 0, "�˳�", "����");
}

MENU MenuChoose() {
    if(msg.x >= 0 && msg.x <= 170){
        if(msg.y >= 60 && msg.y <= 160) return MENU::STUDENT_MGMT;
        else if(msg.y >= 160 && msg.y <= 260) return MENU::TEACHER_MGMT;
        else if(msg.y >= 260 && msg.y <= 360) return MENU::ANNOUNCE_MGMT;
        else if(msg.y >= 360 && msg.y <= 460) return MENU::USER_MGMT;
        else if(msg.y >= 760 && msg.y <= 860) return MENU::END;
    }
    return curGraph;
}

bool userName_ = false;
bool userPassword_ = false;
string s_userName;
string s_userPassword;
bool LoginCheck(const char* identity, pqxx::connection& conn){
    pqxx::work txn(conn);
    // ������ SQL ��ѯ
    string sql = "SELECT COUNT(*) FROM users WHERE user_id = $1 AND password = $2 AND identity = $3";
    pqxx::result result = txn.exec_params(sql, s_userName, s_userPassword, identity);

    // �����������
    if (!result.empty()) {
        int count = result[0][0].as<int>();
        return count > 0; // ��� count > 0��˵���û�����
    }
    return false;
}
std::string LoginGraph(const char* identity, pqxx::connection& conn) {
    Menu(-2);
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    fillrectangle_({220, 0, 1440, 864});
    ClearWindow();
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
    OutputText(loginButton.posx + 35, loginButton.posy + 8, WHITE, 20, 0, "��¼", "����");

    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(-2);

        ButtonAnimation(msg, userNameInputBar, BLACK, LIGHTGRAY, 1);
        ButtonAnimation(msg, userPasswordInputBar, BLACK, LIGHTGRAY, 1);
        ButtonAnimation(msg, loginButton, WHITE, CommonBlue);

        if(userName_) OutputText(userNameInputBar.posx + 10, userNameInputBar.posy + 10, BLACK, 22, 0, s_userName.c_str(), "����");
        else OutputText(userNameInputBar.posx + 10, userNameInputBar.posy + 8, RGB(150, 150, 150), 22, 0, "�������û�id", "����");

        if(userPassword_) OutputText(userPasswordInputBar.posx + 10, userPasswordInputBar.posy + 10, BLACK, 22, 0, s_userPassword.c_str(), "����");
        else OutputText(userPasswordInputBar.posx + 10, userPasswordInputBar.posy + 8, RGB(150, 150, 150), 22, 0, "�������û�����", "����");

        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        if(curGraph == MENU::END) return " ";
                    }
                    if (isInside(msg, userNameInputBar)){
                        fillroundrect_(userNameInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "�������û�id");
                        userName_ = true;
                        s_userName = s;
                    }
                    else if (isInside(msg, userPasswordInputBar)){
                        fillroundrect_(userPasswordInputBar);
                        char s[100] = " ";
                        InputBox(s, 100, "�������û�����");
                        userPassword_ = true;
                        s_userPassword = s;
                    }
                    else if(isInside(msg, loginButton)){
                        if(userName_ && userPassword_ && LoginCheck(identity, conn)){
                            return s_userName;
                        }
                        else{
                            HWND er = GetHWnd();
                            MessageBox(er, "�û������������", "����", MB_OK);
                        }
                    }
            }
        }
    }
}