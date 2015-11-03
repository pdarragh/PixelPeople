/*
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

typedef std::vector< std::vector<Cell> > CELL_MATRIX;

class Frame
{
public:
    // Constructors.
    Frame();
    Frame(int length);
    Frame(int length, QColor color);
    // Methods.
    CELL_MATRIX getCells();
private:
    CELL_MATRIX cells;
};

#endif
