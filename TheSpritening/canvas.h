#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>

class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QObject *parent = 0);
   // virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
   // virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void clear();

signals:

public slots:

private:
    QList <QPointF> m_points;
};

#endif // CANVAS_H
