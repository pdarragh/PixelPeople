/****
 * controller.h
 *
 * The brains behind everything. The Controller is responsible for relaying
 * information between the View and the Model.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QColor>
#include <QPointF>
#include "sprite.h"

class Canvas;

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
    Controller(int available_length);
    void registerCanvas(Canvas* canvas);
    void canvasClickedAtPosition(QPointF point);
    int getViewSideLength();
    QPointF getCellAddressFromPositionInView(QPointF position);
    QPointF getViewPositionFromCellAddress(int x, int y);
    Tools::tool current_tool;
private:
    // Tool methods.
    void usePencilAtPoint(QPointF point);
    void useEraserAtPoint(QPointF point);
    void useRotateAtPoint(QPointF point);
    void useMirrorAtPoint(QPointF point);
    // For doing math on the canvas.
    static int DEFAULT_DIMENSION;
    int dimension;
    int side_length;
    int cell_size;
    // The model hook-in.
    Sprite sprite;
    // The attributes for drawing.
    Canvas* canvas;
    QColor active_color;
};

#endif
