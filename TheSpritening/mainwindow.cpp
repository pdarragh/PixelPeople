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

    // Initiali vector initialization.
    frames = std::vector<Canvas*>();

    // Create the controller and canvas for the graphics view.
    this->controller = Controller(this);

    // Create the main editor Canvas.
    int available_length = getEditorCanvasSize();
    // side_length = controller.getViewSideLength();
    scene = new Canvas(controller.getCurrentFrame(), available_length, true, &controller, this);
    // scene->is_Main_Canvas = true;

    //set the frame graphics view to have this new scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, getEditorCanvasSize(), getEditorCanvasSize());

    //set the alignment for the frame holder
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    //set values for horizontal slider
    ui->horizontalSlider->setValue(3);
    ui->horizontalSlider->setRange(1, 65);

    //instantiate timer
    play_timer = new QTimer(this);

    //connect the clear button and the add frame button
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));
    connect(ui->playPause, SIGNAL(released()), this, SLOT(pplayButtonReleased()));
    connect(ui->backward, SIGNAL(released()), this, SLOT(pbackButtonReleased()));
    connect(ui->forward, SIGNAL(released), this, SLOT(pskipButtonReleased()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(fpsValueChanged(int)));
    connect(play_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    connect(ui->preview, SIGNAL(released()), this, SLOT(on_preview_released()));

    addFramePushed();
    play_timer->start(3000);
}

int MainWindow::getEditorCanvasSize()
{
    QRect rcontent = ui->graphicsView->contentsRect();
    return std::min(rcontent.width(), rcontent.height());
}

void MainWindow::switchEditorToFrame(int index)
{
    scene->clear();
    controller.populateCanvasFromFrame(scene, index);
}

void MainWindow::clearPushed()
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    //clear the scenes and update both views
    scene->clear();
    ui->graphicsView->viewport()->update();
   // ui->graphicsView1->viewport()->update();
    frames[controller.getCurrentFrame() - 1]->clear();
}

void MainWindow::addFramePushed()
{

    //tell the controller so we can add it to the model
    controller.newFrameAdded();

    //create the graphics view for the frame holder
    QGraphicsView* newFrame;
    newFrame = new QGraphicsView;

    //TODO: This should probably be gotten a better way, but I dunno how. /shrug
    int placeholder_width = 77;
    //create the canvas for the graphics view
    Canvas* newScene;
    newScene = new Canvas(controller.getCurrentFrame(), placeholder_width, false, &controller, this);
    frames.push_back(newScene);
    newFrame->setScene(newScene);
    newFrame->setSceneRect(0, 0, placeholder_width, placeholder_width);
    newFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Append the frame to the bottom mini-frame view.
    //ui->horizontalLayout->insertWidget(frames.size(), newFrame);
    qDebug() << "controler " << controller.getCurrentFrame() << "cont plus 1 "<< controller.getCurrentFrame() + 1;

    ui->horizontalLayout->insertWidget(controller.getCurrentFrame() + 1, newFrame);


    // Wipe the main editor;
    scene->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_preview_released()
{
    preview full_preview;
    full_preview.setModal(true);
    full_preview.setController(&controller);
    //full_preview.setFrames(&controller.sprite.getAllFrames());
    full_preview.exec();
}

void MainWindow::drawSpritePixelInCanvasAtCellAddressWithColor(
    int         frame,
    CellAddress address,
    QColor      color   )
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    qDebug() << "frame: " << frame;
    qDebug() << "address: " << address;
    frames[frame]->drawSpritePixelAtCellAddressWithColor(address, color);
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
    //get the current frame that was clicked

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
        if (temp_frame_int != 0) {
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
        temp_frame_int = 0;
    }

    // Updates to the current frame
    temp_frame = the_sprite.getFrame(temp_frame_int);
    QRect preview_content = ui->graphicsView_2->contentsRect();
    //int length_ = std::min(preview_content.width(), preview_content.height());
    int preview_width = 140;
    Canvas* preview_scene = new Canvas(0, preview_width, false, &controller, this);
    preview_scene->setPixelScaleFromSideLength(140);
    //preview_scene->is_Main_Canvas = false;

    // Sets the graphicsView_2 to display this new scene
    ui->graphicsView_2->setScene(preview_scene);
    ui->graphicsView_2->setSceneRect(0, 0, 140, 140);
    ui->graphicsView_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    preview_scene->clear();


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
