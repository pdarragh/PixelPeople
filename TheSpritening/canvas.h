#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QList>
#include <QPainter>
#include "controller.h"

// Tools
namespace CanvasTypes {
    enum type {
        Editor,
        MiniCanvas,
        Preview
    };
};

class Canvas : public QGraphicsScene
{
public:
    // Constructor
    explicit Canvas(int frame_number, int side_length, CanvasTypes::type canvas_type, Controller* controller, QObject *parent = 0);
    // Modifier
    void incrementFrameNumber();
    void decrementFrameNumber();
    void setPixelScaleFromSideLength(float side_length);
    // Clear the scene
    void clear();
    // Pixel scaling
    CellAddress getCellAddressFromPositionInView(ViewPoint position);
    ViewPoint getViewPositionFromCellAddress(CellAddress address);
    // Drawing
    void drawSpritePixelAtCellAddressWithColor(CellAddress address, QColor color);
    void eraseSpritePixelAtCellAddress(CellAddress address);
    // Registering mouse clicks
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

signals:

public slots:

private:
    // Attributes
    CanvasTypes::type canvas_type;
    int frame_number;
    float pixel_scale;
    QColor color;
    QList <ViewPoint> m_points;
    Controller* controller;
};

#endif // CANVAS_H
