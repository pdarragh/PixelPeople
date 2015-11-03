#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //scene for the graphics view
    scene = new GraphicsScene();

    //sets the size of the scene to fit the graphics view
    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    //set the scene of the graphics view
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
