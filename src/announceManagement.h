//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_ANNOUNCEMANAGEMENT_H
#define CPP_SE_ANNOUNCEMANAGEMENT_H

// object
extern object announcementsListButton;
extern object announcementsCommitButton;
extern object announcementsCreateButton;
extern object announcementsArticleInputBar;
extern object announcementsTitleInputBar;
// bool
extern bool announcementsList_;
extern bool announcementsEdit_;
// string
extern std::string s_title;
extern std::string s_article;
// 公告列表存储
extern pqxx::result announcementsList;
// 公告管理界面
void AnnouncementManagementGraph(pqxx::connection& conn);
// 获得公告
void GetAnnouncements(pqxx::connection& conn);
// 公告列表界面
void AnnouncementsList(pqxx::connection& conn);
// 公告编辑界面
void AnnouncementsEdit(pqxx::connection& conn, int announceIndex = -1);
// 公告更新
void UpdateAnnouncement(pqxx::connection& conn);
#endif //CPP_SE_ANNOUNCEMANAGEMENT_H
