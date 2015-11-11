#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QList>
#include <QPainter>
#include "controller.h"

class Canvas : public QGraphicsScene
{
public:
    QColor color;

    explicit Canvas(int frame_number, int side_length, bool is_edit_canvas, Controller* controller, QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    // void drawSquareAtPositionWithColor(QPointF point, int width, int height, QColor color);
    void clear();
    bool is_edit_canvas;
    int frame_number;
    float pixel_scale;
    // Pixel scaling
    CellAddress getCellAddressFromPositionInView(ViewPoint position);
    ViewPoint getViewPositionFromCellAddress(CellAddress address);
    // Drawing
    void drawSpritePixelAtCellAddressWithColor(CellAddress address, QColor color);

signals:

public slots:

private:
    QList <ViewPoint> m_points;
    Controller* controller;
};

#endif // CANVAS_H
