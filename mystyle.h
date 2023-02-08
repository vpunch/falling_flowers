#ifndef MYSTYLE_H
#define MYSTYLE_H

#include <QCommonStyle>
#include <QStyleOptionButton>
#include <QPainter>
#include <QPushButton>
#include <QMargins>

class MyStyle
        :public QCommonStyle
{
public:
    MyStyle();
    void drawPrimitive(PrimitiveElement pe, const QStyleOption *popt, QPainter *pp, const QWidget *pwidget=nullptr ) const;
    void drawControl(ControlElement ce, const QStyleOption *popt, QPainter *pp, const QWidget *pwidget = nullptr ) const;
};

#endif // MYSTYLE_H
