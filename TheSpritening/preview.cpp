#include "preview.h"
#include "ui_preview.h"

preview::preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preview)
{
    ui->setupUi(this);
}

preview::~preview()
{
    delete ui;
}
