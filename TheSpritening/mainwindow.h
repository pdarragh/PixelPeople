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
    ~MainWindow();

private slots:
     void fullPreviewButtonReleased();
     void fpsValueChanged(int value);
     void pplayButtonReleased();
     void pskipButtonReleased();
     void pbackButtonReleased();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
