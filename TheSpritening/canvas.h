#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
#include <QPainter>
#include "controller.h"

class Canvas : public QGraphicsScene
{
public:
    QColor color;

    explicit Canvas(QObject *parent = 0, Controller* controller = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void drawSquareAtPositionWithColor(QPointF point, int width, int height, QColor color);
    void clear();
    bool is_Main_Canvas;
    int frame_number;

signals:

public slots:

private:
    QList <QPointF> m_points;
    Controller* controller;
};

#endif // CANVAS_H
