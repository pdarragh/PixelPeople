#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "canvas.h"
#include "qmath.h"

Canvas::Canvas(
    int         frame_number,
    int         side_length,
    bool        is_edit_canvas,
    Controller* controller,
    QObject     *parent
    ) : QGraphicsScene(parent)
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    this->frame_number = frame_number;
    this->setBackgroundBrush(Qt::gray);
    // int side_length = controller->getViewSideLength();
    this->setSceneRect(0, 0, side_length, side_length);
    this->controller = controller;
    this->is_edit_canvas = is_edit_canvas;
    if (is_edit_canvas)
    {
        this->controller->registerEditor(this);
    }
    this->pixel_scale = float(side_length) / this->controller->getDimension();
    qDebug() << "pixel_scale: " << pixel_scale;
}

//method that takes a qpoint dimension and color
// void Canvas::drawSquareAtPositionWithColor(
//     QPointF point,
//     int     width,
//     int     height,
//     QColor  color   )
// {
//     // Create the rectangle to draw.
//     QGraphicsRectItem* square = this->addRect(point.x(), point.y(), width, height);
//     // Fill the rectangel with colors !
//     square->setBrush(color);
//     square->setPen(color);
// }

void Canvas::drawSpritePixelAtCellAddressWithColor(
    CellAddress address,
    QColor      color   )
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "frame_number: " << frame_number;
    qDebug() << "address: " << address;
    ViewPoint top_left = getViewPositionFromCellAddress(address);
    QGraphicsRectItem* square = this->addRect(top_left.x(), top_left.y(), pixel_scale, pixel_scale);
    square->setBrush(color);
    square->setPen(color);
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "frame_number: " << frame_number;
    if (!is_edit_canvas)
    {
        // Any canvas other than the main editor canvas does not deal with
        // mouse clicks.
        return;
    }
    // Grab the position of the click event.
    ViewPoint click_point = mouseEvent->scenePos();

    // Add the click to the 'm_points' stack and pass the click position to the
    // controller.
    m_points.push_back(click_point);

    // Convert the raw location to a cell address.
    CellAddress address = getCellAddressFromPositionInView(click_point);
    controller->canvasClickedAtCellAddress(address);

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

CellAddress Canvas::getCellAddressFromPositionInView(ViewPoint position)
{
    float x = position.x();
    float y = position.y();
    int cell_x = x / pixel_scale;
    int cell_y = y / pixel_scale;
    return CellAddress(cell_x, cell_y);
}

ViewPoint Canvas::getViewPositionFromCellAddress(CellAddress address)
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "address: " << address;
    qDebug() << "";
    int view_x = address.x() * pixel_scale;
    int view_y = address.y() * pixel_scale;
    return QPointF(view_x, view_y);
}

