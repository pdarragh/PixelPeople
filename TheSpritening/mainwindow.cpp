#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>
#include "preview.h"
#include <QColorDialog>
#include <QDebug>
#include "controller.h"

int MainWindow::DEFAULT_DIMENSION = 64;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initial UI setup.
    ui->setupUi(this);

    // Create the size of the canvas and set up the canvas.
    QRect rcontent = ui->graphicsView->contentsRect();
    int available_length = std::min(rcontent.width(), rcontent.height());

    // Create the controller and canvas for the graphics view.
    this->controller = Controller(available_length);
    side_length = controller.getViewSideLength();
    scene = new Canvas(this, &controller);
    scene->is_Main_Canvas = true;

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, this->side_length, this->side_length);

    //create the canvas for the frame
    //set is_main_canvas to false
    //set frame number to 0
//    QRect rcontent1 = ui->graphicsView1->contentsRect();
//    Canvas* new_frame_scene;
//    new_frame_scene = new Canvas(this, &controller);
//    controller.frame_canvas = new_frame_scene;

//    //set the frame graphics view to have this new scene
//    ui->graphicsView1->setSceneRect(0, 0, rcontent1.width(), rcontent1.height());
    ui->graphicsView1->setScene(scene);

    //set the alignment for the frame holder
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    //connect the clear button and the add frame button
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));
    connect(ui->playPause, SIGNAL(released()), this, SLOT(pplayButtonReleased()));
    connect(ui->forward, SIGNAL(released()), this, SLOT(pskipButtonReleased()));
    connect(ui->backward, SIGNAL(released()), this, SLOT(pbackButtonReleased()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(fpsValueChanged(int)));
    connect(play_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
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

    //create the canvas for the graphics view
    Canvas* newScene;
    newScene = new Canvas(this, &controller);
    newScene->is_Main_Canvas = true;

    //set the scene and insert the graphics view into the horizontal frame holder
    newFrame->setScene(newScene);
    newFrame->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->horizontalLayout->insertWidget(1, newFrame);//TODO:change the 1 to frames.count

    //set the main scene to be the new scene
    ui->graphicsView->setScene(newScene);

    //tell the controller so we can add it to the model
    controller.newFrameAdded();

}


void MainWindow::canvasClickedAtPosition(QPointF point)
{
    //based on the current tool
    //needs coordinate of the box that it was clicked in giveMeCell()
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


void MainWindow::initSmallPreview()
{
    // Set initial scene to something blank
    QGraphicsScene scene;
    QGraphicsView secondView(&scene, this);

    ui->graphicsView_2 = &secondView;
    ui->graphicsView_2->show();
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
        std::cout << "Play is off." << std::endl;
        play_on = true;
    }
}

/*
 * updateTimer
 *
 *
 */
void MainWindow::updateFrame()
{
    //TODO switchout frame
    controller.sprite.getFrame();
    std::vector<Frame> all_frames = controller.sprite.getAllFrames(); // returns a vector which you can then call size on
    all_frames.size(); // use this to calculate the
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
