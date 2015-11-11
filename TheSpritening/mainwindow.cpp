#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>
#include "preview.h"
#include <QColorDialog>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <sstream>
#include "controller.h"

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
    // side_length = controller.getViewSideLength();
    scene = new Canvas(this, &controller);
    scene->is_Main_Canvas = true;

    //set the frame graphics view to have this new scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    //set the alignment for the frame holder
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    ui->horizontalSlider->setValue(3);
    ui->horizontalSlider->setRange(1, 65);

    play_timer = new QTimer(this);

    //connect the clear button and the add frame button
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(fpsValueChanged(int)));
    connect(ui->playPause, SIGNAL(released()), this, SLOT(pplayButtonReleased()));
    connect(play_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));

    play_timer->start(3000);
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

void MainWindow::fpsValueChanged(int value)
{
    play_timer->stop();
    FPS = value;
    play_timer->start(1000 / FPS);

    std::ostringstream ss;
    ss << value;
    std::string changed_int = ss.str();

    std::cout << "FPS changed to " << changed_int << "." << std::endl;
}

/*
 * pplayButtonReleased
 *
 * If play_on is true, the QTimer is started and its interval set to the
 * current fps value.
 */
void MainWindow::pplayButtonReleased()
{
    QIcon *pplayIcon = new QIcon();
    //pplayIcon->addPixmap(QPixmap("new/imageassets/play.png"),QIcon::Normal,QIcon::On);
    pplayIcon->addPixmap(QPixmap(":/new/imageassets/play.png"),QIcon::Normal,QIcon::On);
    //pplayIcon->addPixmap(QPixmap("new/imageassets/pause.png"),QIcon::Normal,QIcon::Off);
    pplayIcon->addPixmap(QPixmap(":/new/imageassets/pause.png"),QIcon::Normal,QIcon::Off);
    ui->playPause->setIcon(*pplayIcon);
    ui->playPause->setCheckable(true);

    // If play_on is true, pressing the button turns it off
    if (play_on)
    {
        // TODO alternates canvas frames
        std::cout << "Play turned off." << std::endl;
        play_timer->stop();

        play_on = false;
    }

    // If play_on is false, pressing the button turns it off
    else
    {
        // TODO allows creates a small things
        std::cout << "Play turned on." << std::endl;
        int msec = 1000 / FPS;
        play_timer->start(msec);

        play_on = true;
    }
}

/*
 * pbackButtonReleased
 *
 * If the tmp frame on display is the first frame, does nothing.
 * Otherwise, goes back one frame.
 */
void MainWindow::pbackButtonReleased()
{
    if (!play_on)
    {
        if (temp_frame_int != 1) {
            temp_frame_int -= 1;
        }
    }
}

/*
 * pskipButtonReleased
 *
 * If the tmp frame on display is the last frame, does nothing.
 * Otherwise, goes forward one frame.
 */
void MainWindow::pskipButtonReleased()
{
    if (!play_on)
    {
        if (temp_frame_int != controller.getSprite().getFrameCount() - 1) {
            temp_frame_int += 1;
        }
    }
}

void MainWindow::updateFrame()
{
    Sprite the_sprite = controller.getSprite();

    if (temp_frame_int == the_sprite.getFrameCount()) {
        temp_frame_int = 1;
    }

    // Updates to the current frame
    temp_frame = the_sprite.getFrame(temp_frame_int);
    QRect preview_content = ui->graphicsView_2->contentsRect();
    int length_ = std::min(preview_content.width(), preview_content.height());
    preview_scene = new Canvas(this, &controller);
    preview_scene->is_Main_Canvas = false;

    // Sets the graphicsView_2 to display this new scene
    ui->graphicsView_2->setScene(preview_scene);
    ui->graphicsView_2->setSceneRect(0, 0, preview_content.width(), preview_content.height());

    // Print testing frames
    std::ostringstream ss;
    ss << temp_frame_int;
    std::string frame_int = ss.str();
    std::cout << "Preview frame: " << frame_int << "." << std::endl;

    std::ostringstream xx;
    xx << the_sprite.getFrameCount();
    std::string frame_count_int = xx.str();
    std::cout << "Total frames: " << frame_count_int << "." << std::endl;

    // Increment frames
    temp_frame_int += 1;
}
