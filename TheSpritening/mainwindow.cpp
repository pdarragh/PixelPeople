#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fullpreview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new Canvas();

    QRect rcontent = ui->graphicsView->contentsRect();

    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    ui->graphicsView->setScene(scene);

    connect(preview_button, SIGNAL(released()), this, SLOT(full_preview_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::full_preview_clicked()
{
    FullPreview full_preview;
    full_preview.setModal(true);
    full_preview.exec();
}
