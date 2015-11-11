#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QTimer>

#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
     Canvas* scene;
     Canvas* preview_scene;
     QColor color;
     QIcon pplayIcon;
     void canvasClickedAtPosition(QPointF point);
     Controller controller;
     QTimer *play_timer;
     int FPS;
     bool play_on = true;
     Frame temp_frame;
     int temp_frame_int = 0;
     // enum class Tools {Eraser, Pencil, Rotate, Mirror};
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    static int DEFAULT_DIMENSION;
    int dimension;
    int side_length;
    int cell_size;

public slots:
    void clearPushed();
    void addFramePushed();

private slots:
    void on_preview_released();
    void on_colorButton_clicked();
    void on_deleteFrameButton_clicked();
    void initSmallPreview();
    void pplayButtonReleased();
    void pbackButtonReleased();
    void pskipButtonReleased();
    void updateFrame();
    void fpsValueChanged(int value);
};

#endif // MAINWINDOW_H
