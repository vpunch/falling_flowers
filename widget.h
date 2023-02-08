#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
//#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QTextDocument>
#include <QTime>

#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>

#include <QScrollBar>
#include <QHeaderView>

#include <QObject>
#include <QSettings>

#include "floweritem.h"
#include "smileitem.h"
#include "twoitem.h"
#include "mystyle.h"

class Widget : public QWidget
{
    Q_OBJECT

    QSettings sett;
    QVector<QObject*> elements;

    short int sec[2];
    short int min[2];
    QTimer *pglobalTimer;

    QTimer *ptwoTimer;
    QTimer *pflowerTimer;
    bool delFlowerMod;
    bool delTwoMod;

    QGraphicsScene *pscene;
    QGraphicsView *pview;

    qint16 flowerInterval;
    qint16 flowerCount;
    qint8 twoCount;

    QGraphicsTextItem *pcongrats;
    QGraphicsTextItem *pcongText;
    QGraphicsProxyWidget *pbtnplay;

    QGraphicsProxyWidget *table;
    QTreeView *view;
    QStandardItemModel *model;
    QGraphicsProxyWidget *btnStart;
    QGraphicsProxyWidget *btnHint;
    QGraphicsTextItem *phTable;

    QGraphicsTextItem *phReg;
    QGraphicsTextItem *pReg;
    QGraphicsProxyWidget *btnUnder;

    QGraphicsTextItem *pttimer;
    QGraphicsTextItem *ptflower;

    QSize windSize;

    void hideAnim(QGraphicsObject *pitem);
    void setTitleAnim(QGraphicsObject *pitem);
    QGraphicsTextItem* createText(const QString& type, const QString& txt, const QFont &font);
    QWidget* createGraphBtn(QGraphicsProxyWidget **pproxWgt, const QString &txt, const QFont &font);

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void resizeEvent(QResizeEvent *pe);

private slots:
    void endGame();
};

#endif // WIDGET_H
