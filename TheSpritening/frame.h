/****
 * frame.h
 *
 * The header for the Frame class. The Frame is responsible for keeping track
 * of all the Cells within a single sprite frame. Multiple frames can be stacked
 * to produce an animation effect, but the frame itself is unaware of this.
 */

#ifndef FRAME_H
#define FRAME_H

#include "cell.h"
#include <vector>
#include <QColor>

typedef std::vector<Cell> CELL_ROW;
typedef std::vector< CELL_ROW > CELL_MATRIX;

class Frame
{
public:
    // Constructors.
    Frame();
    Frame(int length);
    Frame(int length, QColor color);
    Frame(const Frame& other);
    // Methods.
    CELL_MATRIX getCells();
    void setCellAtPositionToColor(int x, int y, QColor color);
    QColor getCellColorAtPosition(int x, int y);
private:
    // Methods.
    void init(int length, QColor color);
    // Attributes.
    static int DEFAULT_LENGTH;
    CELL_MATRIX cells;
};

#endif
