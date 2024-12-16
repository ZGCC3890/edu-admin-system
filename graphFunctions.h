//
// Created by ZGCC on 24-12-16.
//

#ifndef CPP_SE_GRAPHFUNCTIONS_H
#define CPP_SE_GRAPHFUNCTIONS_H

//图形对象
typedef struct object{
    int posx;
    int posy;
    int width;
    int height;
}object;

//重写版fillroundrect（圆角矩形）
void fillroundrect_(object x);
//重写版roundrect（圆角矩形线框）
void roundrect_(object x);
//重写版fillrectangle（矩形）
void fillrectangle_(object x);
//重写版rectangle（圆角矩形线框）
void rectangle_(object x);
//判断是否在object内
bool isInside(ExMessage m, object x);
//输出函数封装（字体颜色，字号，字体，输出位置）
void OutputText(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st);
//按钮效果封装（默认线宽=2，类型为roundrect圆角矩形）
void ButtonAnimation(ExMessage m, object x, COLORREF colorOn, COLORREF colorOff, int lineWidth = 2, std::string sort = "roundrect");
//菜单选中动画
void MenuAnimation(int n);
//重置鼠标
void InitMouseMsg();

#endif //CPP_SE_GRAPHFUNCTIONS_H
