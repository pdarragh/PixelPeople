#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "canvas.h"
#include "qmath.h"

Canvas::Canvas(QObject* parent, Controller* controller) :
    QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::gray);
    int side_length = controller->getViewSideLength();
    // this->setSceneRect(0, 0, side_length, side_length);
    this->controller = controller;
    this->controller->registerCanvas(this);
    qDebug() << "current_tool from canvas: " << this->controller->current_tool;

}

//method that takes a qpoint dimension and color
void Canvas::drawSquareAtPositionWithColor(
    QPointF point,
    int     width,
    int     height,
    QColor  color   )
{
    //erase any item already at this point
    eraseSquareAtPosition(point);
    // Create the rectangle to draw.
    QGraphicsRectItem* square = this->addRect(point.x(), point.y(), width, height);
    // Fill the rectangle with colors !
    square->setBrush(color);
    square->setPen(color);
}

//method that takes a qpoint dimension and color and erases
void Canvas::eraseSquareAtPosition( QPointF point )
{
    QGraphicsItem *item;
    item = itemAt(point,QTransform()); //Get the item at the position
    if (item)
    {
        delete item;
    }
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // Add the click to the 'm_points' stack and pass the click position to the
    // controller.

    m_points.push_back(mouseEvent->scenePos());
    controller->canvasClickedAtPosition(mouseEvent->scenePos());

    // This must be called.
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent * me)
{
    QGraphicsScene::mouseReleaseEvent(me);
}

void Canvas::clear()
{
    QList <QGraphicsItem*> itemList = items();
    while (!itemList.isEmpty())
    {
        delete itemList.first();
        itemList = items();
    }
}
