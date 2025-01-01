//
// Created by ZGCC on 24-12-16.
//

#include "ustil.h"

const int MAXLEN = 10000;

object announcementsListButton = {220, 100, 140, 30};
object announcementsCreateButton = {390, 100, 140, 30};
object announcementsCommitButton = {770, 100, 140, 30};
object announcementsArticleInputBar = {230, 220, 670, 600};
object announcementsTitleInputBar = {400, 165, 500, 30};
std::string s_title;
std::string s_article;

pqxx::result announcementsList;
bool announcementsList_ = true;
bool announcementsEdit_ = false;
bool articleEdit_ = false;

void AnnouncementManagementGraph(pqxx::connection& conn){
    s_adminId = LoginGraph("admin", conn, 2);
    if(s_adminId == " " || s_adminId == "GraphChanged") return;

    ClearWindow(0);
    Menu(2);

    AnnouncementsList(conn);

    while (true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(2);
        ButtonAnimation(msg, announcementsListButton);
        ButtonAnimation(msg, announcementsCreateButton);
        if (announcementsList_) {
            for (int i = 0; i < announcementsList.size(); ++i) {
                ButtonAnimation(msg, {220, 190 + (i % 20) * 30, 400, 30}, CommonBlue, BLACK);
            }
        }
        if (announcementsEdit_) {
            ButtonAnimation(msg, announcementsTitleInputBar, CommonBlue, WHITE);
            ButtonAnimation(msg, announcementsArticleInputBar, CommonBlue, WHITE);
            ButtonAnimation(msg,announcementsCommitButton);
        }
        if (peekmessage(&msg, EM_MOUSE | EX_CHAR)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(MenuChoose() != curGraph) {
                        curGraph = MenuChoose();
                        return;
                    }
                    if (isInside(msg, announcementsCreateButton)) {
                        announcementsEdit_ = true;
                        announcementsList_ = false;
                        AnnouncementsEdit(conn);
                    }
                    if (isInside(msg, announcementsListButton)) {
                        announcementsEdit_ = false;
                        announcementsList_ = true;
                        AnnouncementsList(conn);
                    }
                    if (announcementsList_) {
                        for (int i = 0; i < announcementsList.size(); ++i) {
                            if(isInside(msg, {220, 190 + (i % 20) * 30, 400, 30})){
                                announcementsEdit_ = true;
                                announcementsList_ = false;
                                AnnouncementsEdit(conn, i);
                            }
                        }
                    }
                    if (announcementsEdit_) {
                        if (isInside(msg, announcementsArticleInputBar)){
                            articleEdit_ = true;
                        }else{
                            articleEdit_ = false;
                        }
                        if (isInside(msg, announcementsCommitButton)) {
                            UpdateAnnouncement(conn);
                        }
                        if (isInside(msg, announcementsTitleInputBar)) {
                            char s[100];
                            InputBox(s, 100, "请输入公告标题：");
                            s_title = s;
                            if(s_title.size() < 1) {
                                s_title = "Title";
                            }
                            setfillcolor(WHITE);
                            setlinecolor(BLACK);
                            roundrect_(announcementsTitleInputBar);
                            OutputText(announcementsTitleInputBar.posx + 20, announcementsTitleInputBar.posy + 5, BLACK, s_title.c_str());
                        }
                    }
                    break;
                case WM_CHAR:
                    if(articleEdit_) {
                        switch (msg.ch) {
                            case '\b':
                                if(!s_article.empty())
                                    s_article.erase(s_article.size() - 1);
                                break;
                            default:
                                if(s_article.size() < MAXLEN){
                                    s_article += msg.ch;
                                }
                        }
                        setfillcolor(WHITE);
                        setlinecolor(BLACK);
                        fillrectangle_(announcementsArticleInputBar);
                        OutputText(announcementsArticleInputBar.posx + 20, announcementsArticleInputBar.posy + 10, BLACK, s_article.c_str());
                    }

            }
        }
    }
}

void GetAnnouncements(pqxx::connection& conn) {
    std::string announcementsListSQL = R"(
        SELECT a.title, a.article, TO_CHAR(a.publish_date, 'YYYY-MM-DD') AS publish_date, u.name AS author_name
        FROM announcements a
        JOIN users u ON a.author_id = u.user_id;
    )";
    pqxx::work txn(conn);
    announcementsList = txn.exec_params(announcementsListSQL);
}

void AnnouncementsList(pqxx::connection& conn) {
    ClearWindow(0);
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    fillroundrect_(announcementsListButton);
    fillroundrect_(announcementsCreateButton);
    OutputText(announcementsListButton.posx + 10, announcementsListButton.posy + 5, WHITE, "显示公告列表");
    OutputText(announcementsCreateButton.posx + 20, announcementsCreateButton.posy + 5, WHITE, "创建新公告");
    GetAnnouncements(conn);
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    rectangle_({220, 160, 400, 30});
    rectangle_({620, 160, 200, 30});
    rectangle_({820, 160, 300, 30});
    OutputText(220 + 10, 160 + 5, BLACK, "公告标题");
    OutputText(620 + 10, 160 + 5, BLACK, "作者");
    OutputText(820 + 10, 160 + 5, BLACK, "发布时间");
    for (int i = 0; i < announcementsList.size(); ++i) {
        rectangle_({220, 190 + (i % 20) * 30, 400, 30});
        OutputText(220 + 10, 190 + 5 + (i % 20) * 30, BLACK, announcementsList[i]["title"].as<std::string>().c_str());
        rectangle_({620, 190 + (i % 20) * 30, 200, 30});
        OutputText(620 + 10, 190 + 5 + (i % 20) * 30, BLACK, announcementsList[i]["author_name"].as<std::string>().c_str());
        rectangle_({820, 190 + (i % 20) * 30, 300, 30});
        OutputText(820 + 10, 190 + 5 + (i % 20) * 30, BLACK, announcementsList[i]["publish_date"].as<std::string>().c_str());
    }
}

void AnnouncementsEdit(pqxx::connection& conn, int announcementIndex) {
    ClearWindow(0);
    setfillcolor(CommonBlue);
    setlinecolor(CommonBlue);
    fillroundrect_(announcementsListButton);
    fillroundrect_(announcementsCreateButton);
    fillroundrect_(announcementsCommitButton);
    OutputText(announcementsListButton.posx + 10, announcementsListButton.posy + 5, WHITE, "显示公告列表");
    OutputText(announcementsCreateButton.posx + 20, announcementsCreateButton.posy + 5, WHITE, "创建新公告");
    OutputText(announcementsCommitButton.posx + 30, announcementsCommitButton.posy + 5, WHITE, "确认编辑");
    fillroundrect_({220, 160, 690, 40});
    fillroundrect_({220, 210, 690, 620});
    OutputText(240, 170, WHITE, "标题：");
    if (announcementIndex != -1) {
        s_title = announcementsList[announcementIndex]["title"].as<std::string>();
        s_article = announcementsList[announcementIndex]["article"].as<std::string>();
    }else {
        s_title = s_article = " ";
    }
    setfillcolor(WHITE);
    fillroundrect_(announcementsTitleInputBar);
    fillroundrect_(announcementsArticleInputBar);
    OutputText(announcementsTitleInputBar.posx + 20, announcementsTitleInputBar.posy + 5, BLACK, s_title.c_str());
    OutputText(announcementsArticleInputBar.posx + 20, announcementsArticleInputBar.posy + 10, BLACK, s_article.c_str());
}

void UpdateAnnouncement(pqxx::connection& conn) {
    std::string updateAnnouncementSQL = R"(
        MERGE INTO announcements a
        USING (SELECT $1 AS title, $2 AS article, $3 AS author_id, CURRENT_TIMESTAMP AS current_time FROM DUAL) b
        ON (a.title = b.title)
        WHEN MATCHED THEN
            UPDATE SET a.article = b.article, a.author_id = b.author_id, a.publish_date = b.current_time
        WHEN NOT MATCHED THEN
            INSERT (title, article, author_id)
            VALUES (b.title, b.article, b.author_id);
    )";
    pqxx::work txn(conn);
    txn.exec_params(updateAnnouncementSQL, s_title, s_article, s_adminId);
    txn.commit();
}