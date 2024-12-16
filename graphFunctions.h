//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_GRAPHFUNCTIONS_H
#define CPP_SE_GRAPHFUNCTIONS_H

//ͼ�ζ���
typedef struct object{
    int posx;
    int posy;
    int width;
    int height;
}object;

//��д��fillroundrect��Բ�Ǿ��Σ�
void fillroundrect_(object x);
//��д��roundrect��Բ�Ǿ����߿�
void roundrect_(object x);
//��д��fillrectangle�����Σ�
void fillrectangle_(object x);
//��д��rectangle��Բ�Ǿ����߿�
void rectangle_(object x);
//�ж��Ƿ���object��
bool isInside(ExMessage m, object x);
//���������װ��������ɫ���ֺţ����壬���λ�ã�
void OutputText(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st);
//��ťЧ����װ��Ĭ���߿�=2������ΪroundrectԲ�Ǿ��Σ�
void ButtonAnimation(ExMessage m, object x, COLORREF colorOn, COLORREF colorOff, int lineWidth = 2, std::string sort = "roundrect");
//�˵�ѡ�ж���
void MenuAnimation(int n);
//�������
void InitMouseMsg();

#endif //CPP_SE_GRAPHFUNCTIONS_H
