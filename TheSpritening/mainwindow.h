#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvas.h"

#include <QMainWindow>
#include <QIcon>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
     Canvas * scene;
     Canvas * small_preview;
     QColor color;
     QIcon *pplayIcon = new QIcon();
     void iGotClicked(QPointF point);
     enum class Tools {Eraser, Pencil, Rotate, Mirror};
     bool play_on = true;
     int FPS = 3;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void clearPushed();
    void addFramePushed();

private slots:
    void on_preview_released();
    void on_colorButton_clicked();
    void initSmallPreview();
    void pplayButtonReleased();
    void pbackButtonReleased();
    void pskipButtonReleased();
    void fpsValueChanged(int value);
};

#endif // MAINWINDOW_H
