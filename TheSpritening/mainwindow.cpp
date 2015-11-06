#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>
#include "preview.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Canvas(this);

    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    ui->graphicsView->setScene(scene);


    QRect rcontent1 = ui->graphicsView1->contentsRect();
    ui->graphicsView1->setSceneRect(0, 0, rcontent1.width(), rcontent1.height());
    ui->graphicsView1->setScene(scene);

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));

    ui->horizontalLayout->setAlignment(Qt::AlignLeft);
}
void MainWindow::clearPushed()
{
    scene->clear();
    ui->graphicsView->viewport()->update();
    ui->graphicsView1->viewport()->update();
}

void MainWindow::addFramePushed()
{

//    QRect rcontent2 = ui->graphicsView1->contentsRect();
//    view.setSceneRect(0, 0, rcontent2.width(), rcontent2.height());
//    view.setScene(scene);

    ui->horizontalLayout->insertWidget(1, new QGraphicsView);
}

void MainWindow::iGotClicked(QPointF point)
{
    //based on the current tool
    //needs coordinate of the box that it was clicked in  giveMeCell()
    //call fill cell
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_preview_released()
{
    preview full_preview;
    full_preview.setModal(true);
    full_preview.exec();
}

void MainWindow::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor();

    QString s("background: #"
                                 + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                                 + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                                 + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";");
           ui->colorButton->setStyleSheet(s);
           ui->colorButton->update();

           scene->color = color;
}
