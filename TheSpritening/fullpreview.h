#ifndef FULLPREVIEW_H
#define FULLPREVIEW_H

#include <QDialog>

namespace Ui {
class FullPreview;
}

class FullPreview : public QDialog
{
    Q_OBJECT

public:
    explicit FullPreview(QWidget *parent = 0);
    ~FullPreview();

private:
    Ui::FullPreview *ui;
};

#endif // FULLPREVIEW_H
