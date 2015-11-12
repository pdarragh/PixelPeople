#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QSlider>
#include <QIcon>

#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    void drawSpritePixelInCanvasAtCellAddressWithColor(int frame, CellAddress address, QColor color);
    void switchEditorToFrame(int index);
    void clearFrameAtIndex(int index);
    Canvas* scene;
    Canvas* preview_scene;
    Controller controller;
    int FPS = 3;
    bool play_on = true;
    QTimer *play_timer;
    Frame temp_frame;
    int temp_frame_int = 0;
    // enum class Tools {Eraser, Pencil, Rotate, Mirror};
    ~MainWindow();

private:
    int getEditorCanvasSize();
    std::vector<Canvas*>::iterator getIteratorAtPosition(unsigned long index);
    void rebuildFrameDisplay();
    Ui::MainWindow *ui;
    int dimension;
    int side_length;
    int cell_size;
    std::vector<Canvas*> frames;

public slots:
    void clearPushed();
    void addFramePushed();

private slots:
    void on_preview_released();
    void on_colorButton_clicked();
    void on_deleteFrameButton_clicked();
    void fpsValueChanged(int value);
    void pplayButtonReleased();
    void pbackButtonReleased();
    void pskipButtonReleased();
    void updateFrame();
    void on_clearButton_2_clicked();
};

#endif // MAINWINDOW_H
