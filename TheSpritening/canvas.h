#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
#include<QPainter>

class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QObject *parent = 0);
   // virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
   // virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void doSomething(QPointF point, int x, int y, QColor color);
    void clear();
    QColor color;
    void checkIfNear(QPointF pointToCheck, QGraphicsSceneMouseEvent * mouseEvent);
    QPainter * painter;

signals:

public slots:

private:
    QList <QPointF> m_points;
};

#endif // CANVAS_H
