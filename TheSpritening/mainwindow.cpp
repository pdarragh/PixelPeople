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

    connect(preview_button, SIGNAL(released()), this, SLOT(fullPreviewClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fullPreviewClicked()
{
    FullPreview full_preview;
    full_preview.setModal(true);
    full_preview.exec();
}

/*
 * fpsValueChanged
 *
 * Handling event which sets the time interval for the QTimer object in
 * charge of refreshing the small previewer scene.
 */
void MainWindow::fpsValueChanged(int value)
{

}
