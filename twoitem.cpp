#include "twoitem.h"
#include <QDebug>

TwoItem::TwoItem(qint8 _speed, qint16 _areaWidth, qint16 _areaHeight, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent),
      speedMove(0,0),
      speed(_speed),
      areaWidth(_areaWidth),
      areaHeight(_areaHeight),
      animScale(this, "myscale")
{
    QImage img(75,75, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter pntr(&img);
    pntr.setRenderHint(QPainter::Antialiasing, true);
    pntr.setPen(QPen(QColor("#DF013A"), 6));
    pntr.setBrush(QColor(255, 0, 0, 130));
    pntr.drawEllipse(3,3,img.width()-6, img.height()-6);
    QFont font("", 30);
    font.setBold(true);
    pntr.setFont(font);
    pntr.drawText(img.rect(), Qt::AlignCenter, "2");
    pntr.end();

    setPixmap(QPixmap::fromImage(img));


    timer.setInterval(1000/60);
    timer.start();
    QObject::connect(&timer, &QTimer::timeout, [this]{
        this->moveBy(0+speedMove.x()/3, 0+speedMove.y()/3);
        if(pos().y()>areaHeight || pos().x()>areaWidth || pos().x()+pixmap().width()<0 || pos().y()+pixmap().height()<0)
        {
            if(animScale.state()==QPropertyAnimation::Stopped) {delete this; }
            else connect(&animScale, &QPropertyAnimation::finished, [this]{ delete this; });
        }
    });

    setPos(rand()%(areaWidth-pixmap().width()), rand()%(areaHeight-pixmap().height()));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

    animScale.setDuration(350);
    animScale.setEasingCurve(QEasingCurve::OutQuad);
}

void TwoItem::mousePressEvent(QGraphicsSceneMouseEvent *pe) {
    timer.stop();
    pressPos=pe->pos();
    if(animScale.state()==QPropertyAnimation::Stopped) {
        animScale.setKeyValueAt(0.5, 0.8);
        animScale.setKeyValueAt(1, 1);
        animScale.start();
    }
}

void TwoItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *pe) {
    timer.start();
}

void TwoItem::mouseMoveEvent(QGraphicsSceneMouseEvent *pe) {
    speedMove=pe->pos()-pressPos;
    setPos(pos()+speedMove);
}


