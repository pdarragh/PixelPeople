/****
 * controller.cpp
 *
 * The brains behind everything. The Controller is responsible for relaying
 * information between the View and the Model.
 */

#include <QDebug>
#include "controller.h"

int Controller::DEFAULT_DIMENSION = 64;

Controller::Controller(int available_length)
{
    active_color = Qt::black;
    sprite = Sprite(64, Qt::gray);

    // Do some math to lay out the cells.
    dimension      = DEFAULT_DIMENSION;
    cell_size      = available_length / dimension;
    side_length    = available_length - (available_length % cell_size);

    // Set the default tool.
    current_tool = 0;
}

int Controller::getViewSideLength()
{
    return (cell_size * dimension);
}

void Controller::registerCanvas(Canvas* canvas)
{
    this->canvas = canvas;
}

void Controller::canvasClickedAtPosition(QPointF point)
{
    qDebug() << Q_FUNC_INFO << point;
    qDebug() << "Current tool: " << current_tool;

    switch (current_tool)
    {
        case TOOL_PENCIL:
            usePencilAtPoint(point);
            break;
        case TOOL_ERASER:
            useEraserAtPoint(point);
            break;
        case TOOL_ROTATE:
            useRotateAtPoint(point);
            break;
        case TOOL_MIRROR:
            useMirrorAtPoint(point);
            break;
        default:
            qDebug() << "Something isn't right.";
    }
}

void Controller::usePencilAtPoint(QPointF point)
{
    qDebug() << Q_FUNC_INFO;
}

void Controller::useEraserAtPoint(QPointF point)
{
    qDebug() << Q_FUNC_INFO;
}

void Controller::useRotateAtPoint(QPointF point)
{
    qDebug() << Q_FUNC_INFO;
}

void Controller::useMirrorAtPoint(QPointF point)
{
    qDebug() << Q_FUNC_INFO;
}

QPointF Controller::getCellAddressFromPositionInView(QPointF position)
{
    int x = position.x();
    int y = position.y();
    int cell_x = (x - (x % this->cell_size)) / this->cell_size;
    int cell_y = (y - (y % this->cell_size)) / this->cell_size;
    return QPointF(cell_x, cell_y);
}

QPointF Controller::getViewPositionFromCellAddress(int x, int y)
{
    int view_x = x * this->cell_size;
    int view_y = y * this->cell_size;
    return QPointF(view_x, view_y);
}
