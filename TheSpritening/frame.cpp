/****
 * frame.cpp
 *
 * Implementation details for the Cell class. The Frame is responsible for
 * keeping track of all the Cells within a single sprite frame. Multiple frames
 * can be stacked to produce an animation effect, but the frame itself is
 * unaware of this.
 */

#include "frame.h"

/****
 * Static member attributes
 */
int Frame::DEFAULT_LENGTH = 64;

/****
 * Constructors
 */

Frame::Frame()
{
    init(DEFAULT_LENGTH, QColor(0, 0, 0, 0));
}

Frame::Frame(int length)
{
    init(length, QColor(0, 0, 0, 0));
}

Frame::Frame(
    int     length,
    QColor  color   )
{
    init(length, color);
}

Frame::Frame(const Frame& other)
{
    int length = other.cells.size();
    init(length, QColor(0, 0, 0, 0));
    for (int y = 0; y < length; ++y)
    {
        for (int x = 0; x < length; ++x)
        {
            cells[y][x] = other.cells[y][x];
        }
    }
}

/****
 * Private constructor helper method.
 */

/*
 * init
 *
 * Since each Cell has its own position, we must construct them one-by-one.
 * Therefore we use a nested `for` loop structure to iterate over the 2D array.
 */
void Frame::init(
    int     length,
    QColor  color   )
{
    cells = CELL_MATRIX();
    for (int y = 0; y < length; ++y)
    {
        // Create the base row vector.
        CELL_ROW row;
        for (int x = 0; x < length; ++x)
        {
            // Generate the Cell and stick it in the vector.
            QPoint position = QPoint(x, y);
            row.push_back(Cell(position, color));
        }
        // Push the vector onto the matrix.
        cells.push_back(row);
    }
}

/****
 * Methods
 */

CELL_MATRIX Frame::getCells()
{
    return cells;
}

void Frame::setCellAtPositionToColor(
    int     x,
    int     y,
    QColor  color   )
{
    this->cells[y][x].setColor(color);
}

QColor Frame::getCellColorAtPosition(
    int x,
    int y   )
{
    return this->cells[y][x].getColor();
}

void Frame::clear()
{
    for (CELL_ROW row : cells)
    {
        for (Cell cell : row)
        {
            cell.setColor(QColor(0, 0, 0, 0));
        }
    }
}
