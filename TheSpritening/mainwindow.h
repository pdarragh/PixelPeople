#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

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
    Canvas* scene;
    Controller controller;
    // enum class Tools {Eraser, Pencil, Rotate, Mirror};
    ~MainWindow();

private:
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
};

#endif // MAINWINDOW_H
