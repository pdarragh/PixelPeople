#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>

#include "canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     Canvas * scene;
     QColor color;
     void iGotClicked(QPointF point);
     enum class Tools {Eraser, Pencil, Rotate, Mirror};
    ~MainWindow();

private slots:
     void fullPreviewButtonReleased();
     void fpsValueChanged(int value);
     void pplayButtonReleased();
     void pskipButtonReleased();
     void pbackButtonReleased();

private:
    Ui::MainWindow *ui;

public slots:
    void clearPushed();
    void addFramePushed();

private slots:
    void on_preview_released();
    void on_colorButton_clicked();
};

#endif // MAINWINDOW_H
