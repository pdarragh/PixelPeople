#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <qmath.h>
#include "preview.h"
#include <QColorDialog>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <sstream>
#include <QFileDialog>
#include "controller.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initial UI setup.
    ui->setupUi(this);

    Dialog* new_sprite = new Dialog;
    if( new_sprite->exec() == QDialog::Accepted )
    {

        user_selected_dimension = new_sprite->dimension;
        qDebug() << "dimension selected: " << user_selected_dimension;
        //return;
    }
    // Initiali vector initialization.
    frames = std::vector<Canvas*>();

    // Create the controller and canvas for the graphics view.
    this->controller = Controller(this, user_selected_dimension);
    ui->pencil->setStyleSheet("border:1px solid black;");
    controller.setCurrentTool(Tools::Pencil);

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

void MainWindow::clearMiniCanvas(int frame)
{
    frames[frame]->clear();
}

void MainWindow::clearPushed()
{
    qDebug() << "-------------------------------";
    qDebug() << Q_FUNC_INFO;
    //clear the scenes and update both views
    scene->clear();
    ui->graphicsView->viewport()->update();
    frames[controller.getCurrentFrame()]->clear();
    controller.clearCurrentFrame();
}

void MainWindow::addFramePushed()
{
    int placeholder_width = 77;

    if(frames.size() > 11)
    {
        return;
    }

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
        // This this is right?
        controller.newFrameAddedAtCurrentIndex();

        qDebug() << "Second Option!!";

        //create the new frame
        Canvas* newScene;
        newScene = new Canvas(controller.getCurrentFrame(), placeholder_width, CanvasTypes::MiniCanvas, &controller, this);

        //Insert at index into frames
        frames.insert(getIteratorAtPosition(controller.getCurrentFrame()), newScene);

        //increment frame_number in canvisi
        std::vector<Canvas*>::iterator iterator = getIteratorAtPosition(controller.getCurrentFrame() + 1);
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
        controller.populateCanvasFromFrame(newScene, i);
    }
}

void MainWindow::on_preview_released()
{
    preview full_preview;
    full_preview.setFPS(FPS);
    full_preview.setController(&controller);
    full_preview.setModal(true);
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

void MainWindow::eraseSpritePixelInCanvasAtCellAddress(
    int         frame,
    CellAddress address )
{
    frames[frame]->eraseSpritePixelAtCellAddress(address);
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
    // user can't delete the only freaking frame
    if(frames.size() == 1)
    {
        return;
    }

    // remove frame from frames
    frames.erase(getIteratorAtPosition(controller.getCurrentFrame()));

    // decrement the frame_number of frames after the item
    std::vector<Canvas*>::iterator iterator = getIteratorAtPosition(controller.getCurrentFrame());
    while(iterator != frames.end())
    {
        Canvas* curr = *(iterator);
        curr->decrementFrameNumber();
        iterator++;
    }

    // remove frame from model
    controller.frameRemovedAtCurrentIndex();
    rebuildFrameDisplay();
    switchEditorToFrame(controller.getCurrentFrame());
}

void MainWindow::on_eraser_clicked()
{
    ui->pencil->setStyleSheet("");
    ui->eraser->setStyleSheet("border:1px solid black;");
    switch (controller.current_tool)
    {
        case Tools::MirrorEraser:
        case Tools::MirrorPencil:
            controller.setCurrentTool(Tools::MirrorEraser);
            break;
        default:
            controller.setCurrentTool(Tools::Eraser);
    }
}

void MainWindow::on_pencil_clicked()
{
    ui->eraser->setStyleSheet("");
    ui->pencil->setStyleSheet("border:1px solid black;");
    switch (controller.current_tool)
    {
        case Tools::MirrorPencil:
        case Tools::MirrorEraser:
            controller.setCurrentTool(Tools::MirrorPencil);
            break;
        default:
            controller.setCurrentTool(Tools::Pencil);
    }
}

void MainWindow::on_mirror_clicked()
{
    switch (controller.current_tool)
    {
        case Tools::Pencil:
            controller.setCurrentTool(Tools::MirrorPencil);
            ui->mirror->setStyleSheet("border:1px solid black;");
            break;
        case Tools::Eraser:
            controller.setCurrentTool(Tools::MirrorEraser);
            ui->mirror->setStyleSheet("border:1px solid black;");
            break;
        case Tools::MirrorPencil:
            controller.setCurrentTool(Tools::Pencil);
            ui->mirror->setStyleSheet("");
            break;
        case Tools::MirrorEraser:
            controller.setCurrentTool(Tools::Eraser);
            ui->mirror->setStyleSheet("");
            break;
        default:
            qDebug() << "Something isn't right.";
    }
}

void MainWindow::on_flip_clicked()
{
    controller.flipCurrentFrame();
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
    pplayIcon->addPixmap(QPixmap(":/new/imageassets/pause.png"),QIcon::Normal,QIcon::On);
    pplayIcon->addPixmap(QPixmap(":/new/imageassets/play.png"),QIcon::Normal,QIcon::Off);
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

void MainWindow::on_actionSave_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Files (.)"));
    qDebug() << "Save file name: " << file_name;

    file_name.append(".ssp");
    controller.saveSpriteToFile(file_name);
}

void MainWindow::on_actionSave_2_triggered()
{
     QString load_file_name = QFileDialog::getOpenFileName(this, "Select a file to open...", QDir::homePath());

     qDebug() << "load file name: " << load_file_name;

     controller.loadSpriteFromFile(load_file_name);

}

void MainWindow::on_actionNew_triggered()
{
    Dialog* new_sprite = new Dialog;

    if( new_sprite->exec() == QDialog::Accepted )
    {

        user_selected_dimension = new_sprite->dimension;
        qDebug() << "dimension selected: " << user_selected_dimension;
        this->controller.setUpNewSpriteProject(user_selected_dimension);
        return;
    }
    else
    {
        return;
    }

}

void MainWindow::setUpLoadedSprite(std::vector<Frame> frame_stack)
{
    frames = std::vector<Canvas*>();
    int placeholder_width = 64;
    // add frames to frames
    for(int i = 0; i < frame_stack.size(); i++)
    {
        Canvas* newScene;
        newScene = new Canvas(i, placeholder_width, CanvasTypes::MiniCanvas, &controller, this);
        frames.push_back(newScene);
    }

    // switch editor to current sprite
    switchEditorToFrame(controller.getCurrentFrame());

    // reset frame list
    rebuildFrameDisplay();

}

void MainWindow::setUpNewSprite()
{
    frames = std::vector<Canvas*>();
    int placeholder_width = 64;

    int available_length = getEditorCanvasSize();
    // side_length = controller.getViewSideLength();
    scene = new Canvas(controller.getCurrentFrame(), available_length, CanvasTypes::Editor, &controller, this);
    // scene->is_Main_Canvas = true;

    //set the frame graphics view to have this new scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0, 0, getEditorCanvasSize(), getEditorCanvasSize());

    addFramePushed();
    switchEditorToFrame(controller.getCurrentFrame());
}

void MainWindow::on_pushButton_clicked()
{
    int placeholder_width = 77;

    if(frames.size() > 11)
    {
        return;
    }

    if(controller.getCurrentFrame() == (frames.size() - 1)) // add to end of frames list
    {
        controller.newCopyFrameAdded();

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
        // This this is right?
        controller.newCopyFrameAddedAtCurrentIndex();

        qDebug() << "Second Option!!";

        //create the new frame
        Canvas* newScene;
        newScene = new Canvas(controller.getCurrentFrame(), placeholder_width, CanvasTypes::MiniCanvas, &controller, this);

        //Insert at index into frames
        frames.insert(getIteratorAtPosition(controller.getCurrentFrame()), newScene);

        //increment frame_number in canvisi
        std::vector<Canvas*>::iterator iterator = getIteratorAtPosition(controller.getCurrentFrame() + 1);
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

    // Wipe the main editor;
    scene->clear();
    switchEditorToFrame(controller.getCurrentFrame());
}
