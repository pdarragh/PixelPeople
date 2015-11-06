#ifndef FULLPREVIEW_H
#define FULLPREVIEW_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class FullPreview;
}

class FullPreview : public QDialog
{
    Q_OBJECT

public:
    explicit FullPreview(QWidget *parent = 0);
    ~FullPreview();

private slots:
    void on_exit_button_clicked();

private:
    Ui::FullPreview *ui;
};

#endif // FULLPREVIEW_H
