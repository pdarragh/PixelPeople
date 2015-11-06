/****
 * sprite.h
 *
 * The header for the Sprite class. The Sprite is responsible
 * for maintaining a stack of Frames. A Sprite represents a collection
 * of Frames that can be stacked together to produce an animation
 * effect.
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "frame.h"
#include <QColor>

class Sprite
{
public:
    // Constructors.
    Sprite();
    Sprite(int dimension);
    Sprite(int dimension, QColor color);
    Sprite(std::vector<Frame> frameStack, int dimension);
    // Methods.
    Frame getFrame(int index);
    std::vector<Frame> getAllFrames();
    Frame getNewFrame();
    Frame getNewFrameAfterIndex(int index);
    Frame getNewCopyFrameAfterIndex(int index);
    void removeFrameAtIndex(int index);
    void setCellAtPositionToColor(int x, int y, QColor color);
    QColor getBGColor();
    void setBGColor(QColor color);
    int getDimension();
private:
    // Attributes
    static int DEFAULT_LENGTH;
    static QColor DEFAULT_COLOR;
    std:vector<Frame> frames;
    int current_index;
    int dimension;
    QColor bg_color;
    // Methods.
    std::vector<Frame>::iterator getIteratorAtPosition(int index);

};

#endif // SPRITE

