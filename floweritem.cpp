#include "floweritem.h"

#include <QDebug>

FlowerItem::FlowerItem(qint8 _speed, qint16 _areaWidth, qint16 _areaHeight, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent),
      animRotate(this, "myrotate"),
      speed(_speed),
      areaWidth(_areaWidth),
      areaHeight(_areaHeight)
{
    setPixmap(QPixmap(":/flower.png").scaled(75, 75, Qt::KeepAspectRatio));

    timer.setInterval(1000/60);
    timer.start();
    QObject::connect(&timer, &QTimer::timeout, [this]{
       this->moveBy(0, speed);
       if(pos().y()>areaHeight) {
           delete this;
       }
    });

    setPos(rand()%(areaWidth-pixmap().width()), -pixmap().height());
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

    animRotate.setLoopCount(-1);
    animRotate.setDuration(2400);
    animRotate.setEasingCurve(QEasingCurve::Linear);
    animRotate.setEndValue(180);
    animRotate.start();

}

void FlowerItem::mousePressEvent(QGraphicsSceneMouseEvent *pe) {

    if(opacity()!=1){return;}
    timer.stop();
    QPropertyAnimation *animScale = new QPropertyAnimation(this, "myscale");
    animScale->setDuration(500);
    animScale->setEasingCurve(QEasingCurve::OutQuad);
    animScale->setKeyValueAt(0.5, 1.2);
    animScale->setKeyValueAt(1, 1);
    QPropertyAnimation *animOpa = new QPropertyAnimation(this, "myopa");
    animOpa->setDuration(500);
    animOpa->setEasingCurve(QEasingCurve::OutQuad);
    animOpa->setEndValue(0);

    QParallelAnimationGroup *animGr = new QParallelAnimationGroup;
    animGr->addAnimation(animScale);
    animGr->addAnimation(animOpa);
    animGr->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animGr, &QAbstractAnimation::finished, [this]{
        emit clicked();
        delete this;
    });
}
