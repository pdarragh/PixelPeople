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

    explicit Canvas(QObject *parent = 0, Controller* controller = 0, int side_length = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void drawSquareAtPositionWithColor(QPointF position, QColor color);
    QPointF getCellAddressFromPositionInView(QPointF position);
    QPointF getViewPositionFromCellAddress(int x, int y);
    void clear();
    bool is_Main_Canvas;
    bool first_click;

signals:

public slots:

private:
    float cell_size;
    int my_frame_number;
    QList <QPointF> m_points;
    Controller* controller;
};

#endif // CANVAS_H
