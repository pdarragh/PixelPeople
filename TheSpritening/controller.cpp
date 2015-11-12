/****
 * controller.cpp
 *
 * The brains behind everything. The Controller is responsible for relaying
 * information between the View and the Model.
 */

#include <QDebug>
#include <QFile>
#include <QGraphicsItem>
#include "controller.h"
#include "canvas.h"
#include "mainwindow.h"

int Controller::DEFAULT_DIMENSION = 16;

Controller::Controller()
{
    qDebug() << "-------------------------------";
    qDebug() << "Default controller constructor called.";
}

Controller::Controller(MainWindow* main_window)
{
    current_frame = -1;
    // Do some math to lay out the cells and set up other variables.
    dimension       = DEFAULT_DIMENSION;
    active_color    = Qt::black;
    sprite          = Sprite(dimension, QColor(0, 0, 0, 0));
    this->main_window = main_window;

    // Set the default tool.
    current_tool = Tools::Pencil;
    //qDebug() << "Current tool: " << current_tool;
}

Controller::Controller(MainWindow* main_window, int user_dimension)
{
    current_frame = -1;
    // Do some math to lay out the cells and set up other variables.
    dimension       = user_dimension;
    active_color    = Qt::black;
    sprite          = Sprite(dimension, QColor(0, 0, 0, 0));
    this->main_window = main_window;

    // Set the default tool.
    current_tool = Tools::Pencil;
    //qDebug() << "Current tool: " << current_tool;
}


void Controller::newFrameAdded()
{
    sprite.getNewFrame();
    current_frame += 1;
}

void Controller::newFrameAddedAtCurrentIndex()
{
    current_frame += 1;
    sprite.getNewFrameAfterIndex(current_frame);
}

void Controller::frameRemovedAtCurrentIndex()
{
    // remove frame from model
    sprite.removeFrameAtIndex(current_frame);

    // figure out where to go after deletion
    if(current_frame == (sprite.getFrameCount() - 1)) // end of list
    {
        current_frame = sprite.getFrameCount() - 1;
    }
    else // middle of list
    {
        current_frame++;
    }
}

void Controller::setActiveColor(QColor color)
{
    this->active_color = color;
}

Sprite Controller::getSprite()
{
    return sprite;
}

int Controller::getDimension()
{
    return dimension;
}

int Controller::getCurrentFrame()
{
    qDebug() << "current_frame: " << current_frame;
    return current_frame;
}

void Controller::registerEditor(Canvas* canvas)
{
    this->editor = canvas;
}

void Controller::populateCanvasFromFrame(Canvas* canvas, int frame_number)
{
    /*
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "frame_number: " << frame_number;
    qDebug() << "sprite.getAllFrames().size(): " << sprite.getAllFrames().size();
    */
    Frame frame = sprite.getFrame(frame_number);
    for (int y = 0; y < dimension; ++y)
    {
        for (int x = 0; x < dimension; ++x)
        {
            QColor color = frame.getCellColorAtPosition(x, y);
            CellAddress cell_address = QPoint(x, y);
            canvas->drawSpritePixelAtCellAddressWithColor(cell_address, color);
        }
    }
}

void Controller::clickInMiniCanvas(int index)
{
     qDebug() << "click in mini canvas " << index;
    // Switch to that canvas!
    current_frame = index;
    main_window->switchEditorToFrame(index);
}

void Controller::clearCurrentFrame()
{
    sprite.clearFrameAtIndex(current_frame);
}

void Controller::flipCurrentFrame()
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    Frame duplicate = sprite.getFrame(current_frame);
    sprite.clearFrameAtIndex(current_frame);
    for (int y = 0; y < dimension; ++y)
    {
        for (int x = 0; x < dimension; ++x)
        {
            QColor color = duplicate.getCellColorAtPosition(x, y);
            CellAddress address = CellAddress(dimension - x - 1, y);
            sprite.setCellAtPositionToColor(address.x(), address.y(), color);
            editor->drawSpritePixelAtCellAddressWithColor(address, color);
            main_window->drawSpritePixelInCanvasAtCellAddressWithColor(current_frame, address, color);
        }
    }
}

void Controller::canvasClickedAtCellAddress(CellAddress address)
{
    /*
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "address: " << address;
    qDebug() << "current_tool: " << current_tool;
    */

    switch (current_tool)
    {
        case Tools::Pencil:
            usePencilAtCellAddress(address);
            break;
        case Tools::Eraser:
            useEraserAtCellAddress(address);
            break;
        case Tools::Rotate:
            useRotateAtCellAddress(address);
            break;
        case Tools::MirrorPencil:
        case Tools::MirrorEraser:
            useMirrorAtCellAddress(address);
            break;
        default:
            qDebug() << "Something isn't right.";
    }
}

void Controller::usePencilAtCellAddress(CellAddress address)
{
    /*
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "address: " << address;
    */
    sprite.setCellAtPositionToColor(address.x(), address.y(), active_color);
    editor->drawSpritePixelAtCellAddressWithColor(address, active_color);
    main_window->drawSpritePixelInCanvasAtCellAddressWithColor(current_frame, address, active_color);
}

void Controller::useEraserAtCellAddress(CellAddress address)
{
    // qDebug() << "-------------------------------";
    // qDebug() << Q_FUNC_INFO;
    sprite.setCellAtPositionToColor(address.x(), address.y(), QColor(0, 0, 0, 0));
    editor->eraseSpritePixelAtCellAddress(address);
    main_window->eraseSpritePixelInCanvasAtCellAddress(current_frame, address);
}

void Controller::useRotateAtCellAddress(CellAddress address)
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
}

void Controller::useMirrorAtCellAddress(CellAddress address)
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;

    CellAddress flipped = CellAddress((dimension - address.x() - 1), address.y());
    if (current_tool == Tools::MirrorPencil)
    {
        usePencilAtCellAddress(address);
        usePencilAtCellAddress(flipped);
    }
    else if (current_tool == Tools::MirrorEraser)
    {
        useEraserAtCellAddress(address);
        useEraserAtCellAddress(flipped);
    }
}

// Call this like this:
//   controller->setCurrentTool(Tool::Pencil)
// The values are in controller.h
void Controller::setCurrentTool(Tools::tool new_tool)
{
    current_tool = new_tool;
}


void Controller::setUpNewSpriteProject(int dimension)
{
    current_frame = -1;
    // Do some math to lay out the cells and set up other variables.
    this->dimension = dimension;
    active_color    = Qt::black;
    sprite          = Sprite(dimension, QColor(0, 0, 0, 0));

    // Set the default tool.
    current_tool = Tools::Pencil;

    main_window->setUpNewSprite();
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
                output << cell_color.red() << " " << cell_color.green() << " ";
                output << cell_color.blue() << " " << cell_color.alpha();
                if(col == dimension - 1)
                {
                    output << "\n";
                }
                else
                {
                    output << " ";
                }
            }
        }
    }

    file.close();
}

void Controller::loadSpriteFromFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw;
    }

    QTextStream input(&file);

    // get dimensions from file
    QString line = input.readLine();
    QStringList dimension_list = line.split(" ");
    if(dimension_list.size() != 2)
    {
        throw;
    }
    QString height_string = dimension_list[0];
    QString width_string = dimension_list[1];
    bool height_ok = true;
    bool width_ok = true;
    int height = height_string.toInt(&height_ok);
    int width = width_string.toInt(&width_ok);
    if(!height_ok || !width_ok)
    {
        throw;
    }
    int dimension = std::max(height, width);

    // get number of frames
    line = input.readLine();
    QStringList frames_count_list = line.split(" ");
    if(frames_count_list.size() != 1)
    {
        throw;
    }
    QString frame_count_string = frames_count_list[0];
    bool frame_count_ok = true;
    int frame_count = frame_count_string.toInt(&frame_count_ok);
    if(!frame_count_ok)
    {
        throw;
    }

    // start creating frames from file
    std::vector<Frame> frame_stack;

    // set up variables for loop
    QStringList current_row_list;
    int current_color_value = 0;

    QString r_string;
    QString g_string; // haha
    QString b_string;
    QString a_string;

    bool r_ok;
    bool g_ok;
    bool b_ok;
    bool a_ok;

    int r;
    int g;
    int b;
    int a;

    // fill frame with colors from file
    for(int frame_pos = 0; frame_pos < frame_count; frame_pos++)
    {
        Frame new_frame(dimension);
        //current_color_value = 0;
        for(int row = 0; row < height; row++)
        {
            line = input.readLine();
            current_row_list = line.split(" ");
            current_color_value = 0;
            if(current_row_list.size() != (width * 4))
            {
                throw;
            }

            for(int col = 0; col < width; col++)
            {
                // colors are stored as r g b a
                r_string = current_row_list[current_color_value];
                g_string = current_row_list[current_color_value + 1];
                b_string = current_row_list[current_color_value + 2];
                a_string = current_row_list[current_color_value + 3];

                r = r_string.toInt(&r_ok);
                g = g_string.toInt(&g_ok);
                b = b_string.toInt(&b_ok);
                a = a_string.toInt(&a_ok);

                if(!r_ok || !g_ok || !b_ok || !a_ok)
                {
                    throw;
                }

                QColor cell_color(r, g, b, a);
                new_frame.setCellAtPositionToColor(row, col, cell_color);

                // move to the next set of rgba values in row data
                current_color_value += 4;
            }
        }
        frame_stack.push_back(new_frame);
    }

    sprite = Sprite(frame_stack, dimension);
    current_frame = 0;
    main_window->setUpLoadedSprite(sprite.getAllFrames());
}
