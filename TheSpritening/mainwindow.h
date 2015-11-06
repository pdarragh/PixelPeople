#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
     void full_preview_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
