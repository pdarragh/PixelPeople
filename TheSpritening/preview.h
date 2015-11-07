#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>

namespace Ui {
class preview;
}

class preview : public QDialog
{
    Q_OBJECT

public:
    explicit preview(QWidget *parent = 0);
    ~preview();

private:
    Ui::preview *ui;
};

#endif // PREVIEW_H
