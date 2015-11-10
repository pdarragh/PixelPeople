#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preview.h"
#include <qmath.h>
#include <iostream>
#include <sstream>
#include <QColorDialog>
#include <QPainter>

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

    ui->horizontalSlider->setRange(0, 65);
    ui->horizontalSlider->setValue(3);

    initSmallPreview(); // TODO draw canvas on the previewer

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));
    connect(ui->playPause, SIGNAL(released()), this, SLOT(pplayButtonReleased()));
    connect(ui->backward, SIGNAL(released()), this, SLOT(pbackButtonReleased()));
    connect(ui->forward, SIGNAL(released()), this, SLOT(pskipButtonReleased()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(fpsValueChanged(int)));
    connect(play_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

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

/*
 * initSmallPreview
 *
 * The following method adds the small_preview canvas to the small
 * preview scene. We'll be able to draw on this later.
 */
void MainWindow::initSmallPreview()
{
    //small_preview = new Canvas();

    QGraphicsScene scene;
    QPainterPath path;
    //test_scene(&scene);

    // TODO Specify text placement
    QFont font;
    font.setPixelSize(50);

    path.addText(30, 30, font,  tr("Hello World!!!"));
    path.setFillRule(Qt::OddEvenFill);

    scene.addPath(path);


    //scene.addText("Hello World!");

    //QGraphicsView view (&scene);
    //view.show();

    QGraphicsView secondView(&scene, this);

    ui->graphicsView_2 = &secondView;
    //ui->graphicsView_2 = &view;
    //ui->graphicsView_2 = QGraphicsView(&scene);
    //ui->graphicsView_2->show();

}

/*
 * pplayButtonReleased
 *
 * If play_on is true, the QTimer is started and its interval set to the
 * current fps value.
 */
void MainWindow::pplayButtonReleased()
{
    //pplayIcon->addPixmap(QPixmap("new/imageassets/play.png"),QIcon::Normal,QIcon::On);
    pplayIcon->addPixmap(QPixmap("play.png"),QIcon::Normal,QIcon::On);
    //pplayIcon->addPixmap(QPixmap("new/imageassets/pause.png"),QIcon::Normal,QIcon::Off);
    pplayIcon->addPixmap(QPixmap("pause.png"),QIcon::Normal,QIcon::Off);
    ui->playPause->setIcon(*pplayIcon);
    ui->playPause->setCheckable(true);

    if (play_on)
    {
        // TODO alternates canvas frames
        std::cout << "Play is on." << std::endl;
        play_on = false;
        int msec = 1000 / FPS;
        play_timer->start(msec);

    }

    else
    {
        // TODO allows creates a small things
        //toggle();
        std::cout << "Play is off." << std::endl;
        play_on = true;
    }
}

void MainWindow::pbackButtonReleased()
{

}

void MainWindow::pskipButtonReleased()
{

}

void MainWindow::fpsValueChanged(int value)
{
    //FPS value is stored
    FPS = value;
    std::ostringstream ss;
    ss << value;
    std::string changed_int = ss.str();

    std::cout << "FPS changed to " << changed_int << "." << std::endl;
}
