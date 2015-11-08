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
    QColor color;

    explicit Canvas(QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void doSomething(QPointF point, int x, int y, QColor color);
    void clear();

signals:

public slots:

private:
    QList <QPointF> m_points;
};

#endif // CANVAS_H
