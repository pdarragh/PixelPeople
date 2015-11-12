/*
 * cell.cpp
 *
 * Implementation for the Cell class. Cells are what become the pixels in a
 * sprite animation. Cells have position and color.
 */

#include "cell.h"

/*
 * Constructors
 */

Cell::Cell()
{
    position = QPoint(0, 0);        // (0, 0)
    color    = QColor(0, 0, 0, 0);  // black
}

Cell::Cell(QPoint _position)
{
    position = _position;
    color    = QColor(0, 0, 0, 0);  // black
}

Cell::Cell(QPoint _position, QColor _color)
{
    position = _position;
    color    = _color;
}

Cell::Cell(const Cell& other)
{
    position = other.position;
    color    = other.color;
}

/*
 * Methods
 */

const QPoint Cell::getPosition()
{
    return position;
}

const QColor Cell::getColor()
{
    return color;
}

void Cell::setColor(QColor color)
{
    this->color = color;
}
