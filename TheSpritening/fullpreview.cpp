#include "fullpreview.h"
#include "ui_fullpreview.h"

FullPreview::FullPreview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullPreview)
{
    ui->setupUi(this);
}

FullPreview::~FullPreview()
{
    delete ui;
}
