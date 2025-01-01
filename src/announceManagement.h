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
// �����б�洢
extern pqxx::result announcementsList;
// ����������
void AnnouncementManagementGraph(pqxx::connection& conn);
// ��ù���
void GetAnnouncements(pqxx::connection& conn);
// �����б����
void AnnouncementsList(pqxx::connection& conn);
// ����༭����
void AnnouncementsEdit(pqxx::connection& conn, int announceIndex = -1);
// �������
void UpdateAnnouncement(pqxx::connection& conn);
#endif //CPP_SE_ANNOUNCEMANAGEMENT_H
