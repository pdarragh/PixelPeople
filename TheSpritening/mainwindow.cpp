#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include <qmath.h>
#include "preview.h"
#include <QColorDialog>
=======
#include "fullpreview.h"
>>>>>>> develop

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Canvas(this);

    QRect rcontent = ui->graphicsView->contentsRect();
<<<<<<< HEAD
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
=======

    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    ui->graphicsView->setScene(scene);

    connect(preview_button, SIGNAL(released()), this, SLOT(fullPreviewButtonReleased()));
>>>>>>> develop
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< HEAD
void MainWindow::on_preview_released()
{
    preview full_preview;
=======
void MainWindow::fullPreviewButtonReleased()
{
    FullPreview full_preview;
>>>>>>> develop
    full_preview.setModal(true);
    full_preview.exec();
}

<<<<<<< HEAD
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
=======
/*
 * fpsValueChanged
 *
 * Handling event which sets the time interval for the QTimer object in
 * charge of refreshing the small previewer scene.
 */
void MainWindow::fpsValueChanged(int value)
{

}

/*
 * pskipButtonReleased
 *
 * Handling Event which changes the frame being displayed. Proceeds
 * sequentially from the current frame until it reaches the last frame, then
 * stops. Can only be used when the play/pause button has been toggled to
 * pause.
 */
void MainWindow::pskipButtonReleased()
{

}

/*
 * pbackButtonReleased
 *
 * Handling Event which changes the frame being displayed. Works
 * backwards from the current frame until it reaches the first frame,
 * then stops. Can only be used when the play/pause button has been toggled
 * to pause.
 */
void MainWindow::pbackButtonReleased()
{

>>>>>>> develop
}
