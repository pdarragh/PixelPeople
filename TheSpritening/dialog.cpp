#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

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
     qDebug() << "is 8 checked: " << ui->radioButton_4->isChecked();
     dimension = 8;
}

void Dialog::on_radioButton_3_clicked()
{
    qDebug() << "is 64 checked: " << ui->radioButton_3->isChecked();
    dimension = 64;
}

void Dialog::on_radioButton_2_clicked()
{
    qDebug() << "is 32 checked: " << ui->radioButton_2->isChecked();
    dimension = 32;
}

void Dialog::on_radioButton_clicked()
{
    qDebug() << "is 16 checked: " << ui->radioButton->isChecked();
    dimension = 16;
}
