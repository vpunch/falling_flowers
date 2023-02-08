#ifndef SMILEITEM_H
#define SMILEITEM_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class SmileItem
        :public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
    Q_PROPERTY(qreal myscale READ scale WRITE setScale)

    QPointF pressPos;
    QPointF speedMove;

    QTimer timer;
    qint8 speed;
    qint16 areaWidth;
    qint16 areaHeight;

    QPropertyAnimation animScale;


public:
    SmileItem(qint8 _speed, qint16 _areaWidth, qint16 _areaHeight, QGraphicsItem *parent = nullptr);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *pe);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *pe);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *pe);

};

#endif // SMILEITEM_H
