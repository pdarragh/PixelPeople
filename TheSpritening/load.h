#ifndef LOAD_H
#define LOAD_H

//#include "qcanvas.h"

#include <QDialog>
#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class Load;
}

class Load : public QDialog
{
    Q_OBJECT

public:
    explicit Load(QWidget *parent = 0);
    ~Load();

private:
    Ui::Load *ui;
};

#endif // LOAD_H
