#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    QColor color;
    Controller controller;
    // enum class Tools {Eraser, Pencil, Rotate, Mirror};
    ~MainWindow();

private:
    Ui::MainWindow *ui;
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
    void on_pencil_clicked();
    void on_eraser_clicked();
    void on_flip_clicked();
};

#endif // MAINWINDOW_H
