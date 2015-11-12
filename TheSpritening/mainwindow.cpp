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
    scene = new Canvas(controller.getCurrentFrame(), available_length, CanvasTypes::Editor, &controller, this);
    // scene->is_Main_Canvas = true;

    //set the frame graphics view to have this new scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, getEditorCanvasSize(), getEditorCanvasSize());

    //set the alignment for the frame holder
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    //set values for horizontal slider
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setRange(1, 65);

    //instantiate timer
    play_timer = new QTimer(this);
    //connect the clear button and the add frame button
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));
    connect(ui->playPause, SIGNAL(released()), this, SLOT(pplayButtonReleased()));
    connect(ui->backward, SIGNAL(released()), this, SLOT(pbackButtonReleased()));
    connect(ui->forward, SIGNAL(released()), this, SLOT(pskipButtonReleased()));
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
    int placeholder_width = 77;

    if(controller.getCurrentFrame() == (frames.size() - 1)) // add to end of frames list
    {
        controller.newFrameAdded();

        qDebug() << "First Option!!";

        //create the canvas for the graphics view
        Canvas* newScene;
        newScene = new Canvas(controller.getCurrentFrame(), placeholder_width, CanvasTypes::MiniCanvas, &controller, this);
        frames.push_back(newScene);

        // rebuild frame list
        rebuildFrameDisplay();

    }
    else // add after a specific index
    {
        controller.newFrameAdded();

        qDebug() << "Second Option!!";

        //create the new frame
        Canvas* newScene;
        newScene = new Canvas(controller.getCurrentFrame(), placeholder_width, CanvasTypes::MiniCanvas, &controller, this);

        std::vector<Canvas*>::iterator test = getIteratorAtPosition(controller.getCurrentFrame());

        //Insert at index into frames
        frames.insert(getIteratorAtPosition(controller.getCurrentFrame()), newScene);

        //increment frame_number in canvisi
        std::vector<Canvas*>::iterator iterator = getIteratorAtPosition(controller.getCurrentFrame());
        while(iterator != frames.end())
        {
            Canvas* curr = *iterator;
            curr->incrementFrameNumber();
            //(*iterator)->incrementFrameNumber();
            iterator++;
        }

        //rebuild frame list
        rebuildFrameDisplay();
    }

    /*
    //tell the controller so we can add it to the model
    controller.newFrameAdded();

    //create the graphics view for the frame holder
    QGraphicsView* newFrame;
    newFrame = new QGraphicsView;

    //TODO: This should probably be gotten a better way, but I dunno how. /shrug
    int placeholder_width = 77;
    //create the canvas for the graphics view
    Canvas* newScene;
    newScene = new Canvas(controller.getCurrentFrame(), placeholder_width, CanvasTypes::MiniCanvas, &controller, this);
    frames.push_back(newScene);
    newFrame->setScene(newScene);
    newFrame->setSceneRect(0, 0, placeholder_width, placeholder_width);
    newFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Append the frame to the bottom mini-frame view.
    //ui->horizontalLayout->insertWidget(frames.size(), newFrame);
    qDebug() << "controler " << controller.getCurrentFrame() << "cont plus 1 "<< controller.getCurrentFrame() + 1;

    ui->horizontalLayout->insertWidget(controller.getCurrentFrame() + 1, newFrame);
    */

    // Wipe the main editor;
    scene->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rebuildFrameDisplay()
{
    // delete all the things
    QLayoutItem* child;
    while((child = ui->horizontalLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    int placeholder_width = 77;

    for(int i = 0; i < frames.size(); i++)
    {
        QGraphicsView* newFrame = new QGraphicsView;

        Canvas* newScene = frames[i];
        //newScene = new Canvas(i, placeholder_width, false, &controller, this);
        newFrame->setScene(newScene);
        newFrame->setSceneRect(0, 0, placeholder_width, placeholder_width);
        newFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->horizontalLayout->insertWidget(i, newFrame);
    }
}

void MainWindow::on_preview_released()
{
    preview full_preview;
    full_preview.setModal(true);
    full_preview.setFPS(this->FPS);
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
    //set icon for play/pause
    QIcon *pplayIcon = new QIcon();
    pplayIcon->addPixmap(QPixmap(":/new/imageassets/play.png"),QIcon::Normal,QIcon::On);
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

    // If play_on is false, pressing the button turns it on
    else
    {
        // TODO allows creates a small things
        std::cout << "Play turned on." << std::endl;
        int msec = (1000 / FPS);
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
        if (temp_frame_int > 0) {
            temp_frame_int = temp_frame_int - 1;
        }

        updateFrame();
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
        if (temp_frame_int < (controller.getSprite().getFrameCount() - 1)) {
            temp_frame_int = temp_frame_int + 1;
        }

        updateFrame();
    }
}

void MainWindow::updateFrame()
{
    Sprite the_sprite = controller.getSprite();

    // Stores some frame's index number inside of temp_frame
    temp_frame = the_sprite.getFrame(temp_frame_int);

    // Stores contentsRect() inside of preview_content for later size calculations
    QRect preview_content = ui->graphicsView_2->contentsRect();
    //int length_ = std::min(preview_content.width(), preview_content.height());
    int preview_width = 140;
    preview_scene = new Canvas(temp_frame_int, preview_width, CanvasTypes::Preview, &controller, this);

    // Double checks that the Pixel size is set correctly
    preview_scene->setPixelScaleFromSideLength(140);

    // Sets graphicsView_2 to display the correct scene
    ui->graphicsView_2->setScene(preview_scene);
    ui->graphicsView_2->setSceneRect(0, 0, 140, 140);
    ui->graphicsView_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    controller.populateCanvasFromFrame(preview_scene, temp_frame_int);

    // Clears scene immediately afterward
    //preview_scene->clear();

    // Print testing frames
    std::ostringstream ss;
    ss << temp_frame_int;
    std::string frame_int = ss.str();
    std::cout << "Preview frame: " << frame_int << "." << std::endl;

    std::ostringstream xx;
    xx << the_sprite.getFrameCount();
    std::string frame_count_int = xx.str();
    std::cout << "Total frames: " << frame_count_int << "." << std::endl;

    // increment to loop through frames if play is on
    if (play_on) {
        // Increment frames
        temp_frame_int += 1;
    }

    // Make sure that if you reach the end, you go back to the beginning
    if (temp_frame_int == the_sprite.getFrameCount()) {
        temp_frame_int = 0;
    }
}

void MainWindow::on_clearButton_2_clicked()
{
    on_deleteFrameButton_clicked();
}


std::vector<Canvas*>::iterator MainWindow::getIteratorAtPosition(unsigned long index)
{
    std::vector<Canvas*>::iterator new_iterator = frames.begin() + index;
    return new_iterator;
}
