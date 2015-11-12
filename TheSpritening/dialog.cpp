#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_radioButton_4_clicked()
{
     dimension = 8;
}

void Dialog::on_radioButton_3_clicked()
{
    dimension = 64;
}

void Dialog::on_radioButton_2_clicked()
{
    dimension = 32;
}

void Dialog::on_radioButton_clicked()
{
    dimension = 16;
}
