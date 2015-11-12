#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include <QTimer>

#include "frame.h"
#include "controller.h"
#include "canvas.h"

namespace Ui {
class preview;
}

class preview : public QDialog
{
    Q_OBJECT

public:
    explicit preview(QWidget *parent = 0);
    ~preview();
    QTimer *full_timer;
    void setController(Controller* controller);
    void setFPS(int value);
    //void closeEvent(QCloseEvent *Event);
private:
    Ui::preview *ui;
    Frame temp_frame;
    int temp_frame_int = 0;
    Canvas* full_scene;
    Controller* the_controller;
    Sprite the_sprite;

public slots:
    void updateFullPreview();
};

#endif // PREVIEW_H
