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
    Sprite(const Sprite& other);
    // Methods.
    Frame getFrame(unsigned long index);
    std::vector<Frame> getAllFrames();
    int getFrameCount();
    Frame getNewFrame();
    Frame getNewFrameAfterIndex(unsigned long index);
    Frame getNewCopyFrameAfterIndex(unsigned long index);
    void removeFrameAtIndex(unsigned long index);
    void setCellAtPositionToColor(int x, int y, QColor color);
    QColor getBGColor();
    void setBGColor(QColor color);
    int getDimension();
private:
    // Attributes
    static int DEFAULT_LENGTH;
    static QColor DEFAULT_COLOR;
    std::vector<Frame> frames;
    unsigned long current_index;
    int dimension;
    QColor bg_color;
    // Methods.
    std::vector<Frame>::iterator getIteratorAtPosition(unsigned long index);

};

#endif // SPRITE

