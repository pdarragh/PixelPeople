#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "canvas.h"
#include "qmath.h"

Canvas::Canvas(
    int                 frame_number,
    int                 side_length,
    CanvasTypes::type   canvas_type,
    Controller*         controller,
    QObject             *parent     )
    : QGraphicsScene(parent)
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "FUCKING FRAME: " << frame_number;
    this->frame_number = frame_number;
    qDebug() << "FUCKING this->FRAME: " << this->frame_number;
    this->setBackgroundBrush(Qt::gray);
    this->setSceneRect(0, 0, side_length, side_length);
    this->controller = controller;
    this->canvas_type = canvas_type;
    if (canvas_type == CanvasTypes::Editor)
    {
        this->controller->registerEditor(this);
    }
    this->pixel_scale = float(side_length) / this->controller->getDimension();
    qDebug() << "pixel_scale: " << pixel_scale;
}

void Canvas::incrementFrameNumber()
{
    frame_number++;
}

void Canvas::decrementFrameNumber()
{
    frame_number--;
}

void Canvas::setPixelScaleFromSideLength(float side_length)
{
    pixel_scale = side_length / this->controller->getDimension();
    qDebug() << "pixel_scale: " << pixel_scale;
}

void Canvas::drawSpritePixelAtCellAddressWithColor(
    CellAddress address,
    QColor      color   )
{
    /*
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "frame_number: " << this->frame_number;
    qDebug() << "address: " << address;
    */
    ViewPoint view_point = getViewPositionFromCellAddress(address);
    QGraphicsRectItem* square = this->addRect(view_point.x(), view_point.y(), pixel_scale, pixel_scale);
    square->setBrush(color);
    square->setPen(color);
}

void Canvas::eraseSpritePixelAtCellAddress(CellAddress address)
{
    ViewPoint view_point = getViewPositionFromCellAddress(address);
    QGraphicsItem *item;
    item = itemAt(view_point, QTransform());
    if (item)
    {
        // Set the item's color to transparency.
        QGraphicsRectItem* rItem = (QGraphicsRectItem*) item;
        rItem->setBrush(QColor(0, 0, 0, 0));
        QPen pen;
        pen.setWidth(0);
        pen.setColor(QColor(0, 0, 0, 0));
        rItem->setPen(pen);
    }
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    /*
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "frame_number: " << frame_number;
    */
    if (canvas_type == CanvasTypes::MiniCanvas)
    {
        // Any canvas other than the main editor will switch the main view to
        // that canvas.
        controller->clickInMiniCanvas(frame_number);
        return;
    }
    else if (canvas_type == CanvasTypes::Preview)
    {
        // The preview canvases should not register anything on mouse press.
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
    int view_x = address.x() * pixel_scale;
    int view_y = address.y() * pixel_scale;
    return QPointF(view_x, view_y);
}

