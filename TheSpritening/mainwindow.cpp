#include <qmath.h>
#include <QColorDialog>
#include <QDebug>
#include <vector>
#include "controller.h"
#include "preview.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initial UI setup.
    ui->setupUi(this);

    qDebug() << "setting up canvasi";
    this->canvases = std::vector<Canvas*>();
    qDebug() << "canvasi up-set";
    // Create the size of the canvas and set up the canvas.
    QRect rcontent = ui->graphicsView->contentsRect();
    int available_length = std::min(rcontent.width(), rcontent.height());

    // Create the controller and canvas for the graphics view.
    this->controller = Controller(available_length, &(this->canvases));
    this->controller.canvases = &(this->canvases);

    // side_length = controller.getViewSideLength();
    scene = new Canvas(this, &controller, available_length);
    scene->is_Main_Canvas = true;
    this->controller.registerCanvas(scene);


    //set the frame graphics view to have this new scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    //set the alignment for the frame holder
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    QRect fcontent = ui->graphicsView1->contentsRect();
    int f_available_length = std::min(fcontent.width(), fcontent.height());

    Canvas* newScene;
    newScene = new Canvas(this, &controller, f_available_length);
    newScene->is_Main_Canvas = false;
    ui->graphicsView1->setScene(newScene);
    ui->graphicsView1->setSceneRect(0,0, fcontent.width(),fcontent.height());


    //connect the clear button and the add frame button
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));
}

void MainWindow::clearPushed()
{
    //clear the scenes and update both views
    scene->clear();
    ui->graphicsView->viewport()->update();
    ui->graphicsView1->viewport()->update();
}

void MainWindow::addFramePushed()
{
    //create the graphics view for the frame holder
    QGraphicsView* newFrame;
    newFrame = new QGraphicsView;

    this->controller.c_frame_number++;

    //create the canvas for the graphics view
    Canvas* newScene;
    newScene = new Canvas(this, &controller);
    newScene->is_Main_Canvas = true;

    //set the scene and insert the graphics view into the horizontal frame holder
    newFrame->setScene(newScene);
    newFrame->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->horizontalLayout->insertWidget(1, newFrame); //TODO:change the 1 to frames.count

    //set the main scene to be the new scene
    ui->graphicsView->setScene(newScene);

    //tell the controller so we can add it to the model
    //add it to the stack of canvases
    canvases.push_back(newScene);
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

    QString s(
        "background: #" +
        QString(color.red() < 16? "0" : "") + QString::number(color.red(),16) +
        QString(color.green() < 16? "0" : "") + QString::number(color.green(),16) +
        QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
    );
    ui->colorButton->setStyleSheet(s);
    ui->colorButton->update();

    //TODO: get the proper canvas from the model and set the color
    //scene->color = color;
   controller.setActiveColor(color);
}

void MainWindow::on_deleteFrameButton_clicked()
{
    //TODO:remove frame from widget at frame number
    delete ui->horizontalLayout->itemAt(0)->widget();
    delete ui->horizontalLayout->itemAt(0);
}
