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
        Mirror
    };
};

class Controller
{
public:
    // Constructors
    Controller();
    Controller(MainWindow* main_window);
    // Canvas methods
    void registerEditor(Canvas* editor);
    void canvasClickedAtCellAddress(CellAddress address);
    void populateCanvasFromFrame(Canvas* canvas, int frame_number);
    // Mini canvases.
    void newFrameAdded();
    Sprite getSprite();
    // Drawing and tools.
    void setActiveColor(QColor color);
    void setCurrentTool(Tools::tool new_tool);
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
    void saveSpriteToFile(QString filename);
    void loadSpriteFromFile(QString filename);
};

#endif
