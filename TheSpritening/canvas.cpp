#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "canvas.h"
#include "qmath.h"

Canvas::Canvas(QObject* parent, Controller* controller, int side_length) :
    QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::gray);
   // int side_length = controller->getViewSideLength();
    // this->setSceneRect(0, 0, side_length, side_length);
    this->controller = controller;
    //this->controller->registerCanvas(this);

    my_frame_number = this->controller->c_frame_number;
    qDebug() << "my_frame_number: " << my_frame_number;
    qDebug() << "side_length: " << side_length;
    qDebug() << "this->controller->dimension: " << this->controller->dimension;
    this->cell_size = float(side_length) / float(this->controller->dimension);

    qDebug() << "current_tool from canvas: " << this->controller->current_tool;
}

//method that takes a qpoint dimension and color
void Canvas::drawSquareAtPositionWithColor(
    QPointF position,
    QColor  color   )
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "I am canvas: " << my_frame_number;
    QPointF point = getViewPositionFromCellAddress(position.x(), position.y());
    qDebug() << "point: " << point;
    // Create the rectangle to draw.
    QGraphicsRectItem* square = this->addRect(point.x(), point.y(), cell_size, cell_size);
    // Fill the rectangel with colors !
    square->setBrush(color);
    square->setPen(color);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // Add the click to the 'm_points' stack and pass the click position to the
    // controller.
    if(this->is_Main_Canvas)
    {
        qDebug() << "FUF ME";
    }
    else
    {

    }
    QPointF cell_address = getCellAddressFromPositionInView(mouseEvent->scenePos());

    m_points.push_back(mouseEvent->scenePos());

    controller->canvasClickedAtPosition(cell_address);

    // This must be called.
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent * me)
{
    QGraphicsScene::mouseReleaseEvent(me);
}

QPointF Canvas::getCellAddressFromPositionInView(QPointF position)
{
    qDebug() << "position: " << position;
    float x = position.x();
    float y = position.y();
    qDebug() << "cell_size: " << cell_size;
    int cell_x = x / cell_size;
    int cell_y = y / cell_size;
    return QPointF(cell_x, cell_y);
}

QPointF Canvas::getViewPositionFromCellAddress(int x, int y)
{
    int view_x = x * cell_size;
    int view_y = y * cell_size;
    return QPointF(view_x, view_y);
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
