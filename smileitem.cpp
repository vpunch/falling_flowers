#include "smileitem.h"

#include <QDebug>

SmileItem::SmileItem(qint8 _speed, qint16 _areaWidth, qint16 _areaHeight, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent),
      speed(_speed),
      speedMove(0,0),
      areaWidth(_areaWidth),
      areaHeight(_areaHeight),
      animScale(this, "myscale")

{
    setPixmap(QPixmap(":/smile.png").scaled(75, 75, Qt::KeepAspectRatio));

    timer.setInterval(1000/60);
    timer.start();
    QObject::connect(&timer, &QTimer::timeout, [this]{
        this->moveBy(0, speed);
        if(pos().y()>areaHeight) {
            if(animScale.state()==QPropertyAnimation::Stopped) {delete this;}
            else connect(&animScale, &QPropertyAnimation::finished, [this]{
                delete this;
            });
        }
    });

    setPos(rand()%(areaWidth-pixmap().width()), -pixmap().height());
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

//    setFlag(QGraphicsItem::ItemIsMovable);
    animScale.setDuration(350);
    animScale.setEasingCurve(QEasingCurve::OutQuad);
    animScale.setKeyValueAt(0.5, 1.2);
    animScale.setKeyValueAt(1, 1);

}

void SmileItem::mousePressEvent(QGraphicsSceneMouseEvent *pe) {
    timer.stop();
    if(animScale.state()==QPropertyAnimation::Stopped) {
        pressPos=pe->pos();
        animScale.start();
    }
}

void SmileItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *pe) {
    timer.start();
}

void SmileItem::mouseMoveEvent(QGraphicsSceneMouseEvent *pe) {
    speedMove=pe->pos()-pressPos;
    setPos(pos()+speedMove);
}

