#ifndef FLOWERITEM_H
#define FLOWERITEM_H

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class FlowerItem
        :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal myscale READ scale WRITE setScale)
    Q_PROPERTY(qreal myrotate READ rotation WRITE setRotation)
    Q_PROPERTY(qreal myopa READ opacity WRITE setOpacity)


    QPropertyAnimation animRotate;

    QTimer timer;
    qint8 speed;
    qint16 areaWidth;
    qint16 areaHeight;


public:
    FlowerItem(qint8 _speed, qint16 _areaWidth, qint16 _areaHeight, QGraphicsItem *parent = nullptr);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *pe);

signals:
    void clicked();

};

#endif // FLOWERITEM_H
