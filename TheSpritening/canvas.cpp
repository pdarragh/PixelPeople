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
    //get any item at this location
    QGraphicsItem *item;
    item = itemAt(point,QTransform()); //Get the item at the position
    if (item)
    {
      qDebug() << "pos of point" << item->scenePos();
        //set the item's color to the new color
       QGraphicsRectItem* rItem = (QGraphicsRectItem*) item;
       rItem->setBrush(color);
       QPen pen;
       pen.setWidth(0);
       pen.setColor(color);
       rItem->setPen(pen);
       return;
    }
    // Create the rectangle to draw.
    QPen pen;
    pen.setWidth(0);
    pen.setColor(color);
    QGraphicsRectItem* square = this->addRect(point.x(), point.y(), width, height);
    // Fill the rectangle with colors !
    square->setBrush(color);
    square->setPen(pen);
}

//method that takes a qpoint dimension and color and erases
void Canvas::eraseSquareAtPosition( QPointF point )
{
    //QGraphicsItem *item;
    //item = itemAt(point,QTransform()); //Get the item at the position
    //if (item)
    //{
    //    delete item;
    //}

    //get any item at this location
    QGraphicsItem *item;
    item = itemAt(point,QTransform()); //Get the item at the position
    if (item)
    {
      //set the item's color to 0,0,0,0
       QGraphicsRectItem* rItem = (QGraphicsRectItem*) item;
       rItem->setBrush(QColor(0,0,0,0));
       QPen pen;
       pen.setWidth(0);
       pen.setColor(QColor(0,0,0,0));
       rItem->setPen(pen);
       return;
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
