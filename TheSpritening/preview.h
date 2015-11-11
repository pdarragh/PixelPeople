#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class preview;
}

class preview : public QDialog
{
    Q_OBJECT

public:
    explicit preview(QWidget *parent = 0);
    ~preview();
    QTimer *full_timer = new QTimer(this);

private:
    Ui::preview *ui;

public slots:
    void updateFullPreview();
};

#endif // PREVIEW_H
