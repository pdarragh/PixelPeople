#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qDebug() << "is 8 checked: " << ui->radioButton_4->isChecked();
}

Dialog::~Dialog()
{
    delete ui;
}
