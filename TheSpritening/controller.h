/****
 * controller.h
 *
 * The brains behind everything. The Controller is responsible for relaying
 * information between the View and the Model.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QColor>
#include <QPoint>
#include <QPointF>
#include "sprite.h"

class Canvas;
class MainWindow;
typedef QPoint CellAddress;
typedef QPointF ViewPoint;

// Tools
namespace Tools {
    enum tool {
        Pencil,
        Eraser,
        Rotate,
        MirrorPencil,
        MirrorEraser
    };
}

class Controller
{
public:
    // Constructors
    Controller();
    Controller(MainWindow* main_window);
    Controller(MainWindow* main_window, int user_dimension);
    // Canvas methods
    void registerEditor(Canvas* editor);
    void canvasClickedAtCellAddress(CellAddress address);
    void clickInMiniCanvas(int index);
    void populateCanvasFromFrame(Canvas* canvas, int frame_number);
    // Mini canvases.
    void newFrameAdded();
    void newFrameAddedAtCurrentIndex();
    void frameRemovedAtCurrentIndex();
    Sprite getSprite();
    // Drawing and tools.
    void setActiveColor(QColor color);
    void setCurrentTool(Tools::tool new_tool);
    void clearCurrentFrame();

    void loadSpriteFromFile(QString filename);
     void saveSpriteToFile(QString filename);

    void flipCurrentFrame();

    // Attributes.
    int getDimension();
    int getCurrentFrame();
    Tools::tool current_tool;
    Canvas* editor;
private:
    // Tool methods.
    void usePencilAtCellAddress(CellAddress address);
    void useEraserAtCellAddress(CellAddress address);
    void useRotateAtCellAddress(CellAddress address);
    void useMirrorAtCellAddress(CellAddress address);
    // For doing math on the canvas.
    static int DEFAULT_DIMENSION;
    int dimension;
    // The model hook-in.
    Sprite sprite;
    // The view hook-in.
    MainWindow* main_window;
    int current_frame;
    // The attributes for drawing.
    QColor active_color;
    // Save and Load methods.
};

#endif
