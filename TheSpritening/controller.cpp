/****
 * controller.cpp
 *
 * The brains behind everything. The Controller is responsible for relaying
 * information between the View and the Model.
 */

#include <QDebug>
#include <QFile>
#include "controller.h"
#include "canvas.h"

int Controller::DEFAULT_DIMENSION = 64;

Controller::Controller()
{
     qDebug() << "Called" ;
}

Controller::Controller(int available_length)
{
    // Do some math to lay out the cells and set up other variables.
    dimension       = DEFAULT_DIMENSION;
    cell_size       = available_length / dimension;
    side_length     = available_length - (available_length % cell_size);
    active_color    = Qt::black;
    sprite          = Sprite(dimension, Qt::gray);

    // Set the default tool.
    current_tool = Tools::Pencil;
    qDebug() << "Current tool: " << current_tool;
}
void Controller::newFrameAdded()
{
   //get a new frame from the model
  sprite.getNewFrame();

  //set the canvas's frame number
  this->canvas->frame_number = sprite.getAllFrames().size()-1;

  qDebug() << "Frame Count: " << sprite.getAllFrames().size();
}
void Controller::setActiveColor(QColor color)
{
    this->active_color = color;
}

int Controller::getViewSideLength()
{
    return (cell_size * dimension);
}

Sprite Controller::getSprite()
{
    return sprite;
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
        case Tools::Pencil:
            usePencilAtPoint(point);
            break;
        case Tools::Eraser:
            useEraserAtPoint(point);
            break;
        case Tools::Rotate:
            useRotateAtPoint(point);
            break;
        case Tools::Mirror:
            useMirrorAtPoint(point);
            break;
        default:
            qDebug() << "Something isn't right.";
    }
}

void Controller::usePencilAtPoint(QPointF point)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "Point: " << point;
    QPointF cell_address = getCellAddressFromPositionInView(point);
    //TODO: modifications to the sprite
     getViewPositionFromCellAddress(cell_address.x(), cell_address.y());
    // use a different variable down here once this is implemented
     this->canvas->drawSquareAtPositionWithColor(point, cell_size, cell_size, active_color);

     //TODO: i believe to store the new rectangle in the model we call
     sprite.setCellAtPositionToColor(cell_address.x(),cell_address.y(),active_color);
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

// Call this like this:
//   controller->setCurrentTool(Tool::Pencil)
// The values are in controller.h
void Controller::setCurrentTool(Tools::tool new_tool)
{
    current_tool = new_tool;
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

void Controller::saveSpriteToFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    // insert data into f
    QTextStream output(&file);

    // get needed data to save
    int dimension = sprite.getDimension();
    std::vector<Frame> frames = sprite.getAllFrames();
    int number_of_frames = frames.size();

    output << dimension << " " << dimension << "\n";
    output << number_of_frames << "\n";

    for(int frame_pos = 0; frame_pos < number_of_frames; frame_pos++)
    {
        Frame current_frame = frames[frame_pos];
        for(int row = 0; row < dimension; row++)
        {
            for(int col = 0; col < dimension; col++)
            {
                QColor cell_color = current_frame.getCellColorAtPosition(row, col);
                output << cell_color.red() << cell_color.green();
                output << cell_color.blue() << cell_color.alpha();
                output << " ";
                if(col = dimension - 1)
                {
                    output << "\n";
                }
            }
        }
    }

    file.close();
}

void Controller::loadSpriteFromFile(QString filename)
{

}
