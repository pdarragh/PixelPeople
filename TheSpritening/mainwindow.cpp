#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>
#include "preview.h"
#include <QColorDialog>
#include <QDebug>
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

    //connect the clear button and the add frame button
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearPushed()));
    connect(ui->addFrameButton, SIGNAL(clicked()), this, SLOT(addFramePushed()));

    addFramePushed();
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
    ui->horizontalLayout->insertWidget(controller.getCurrentFrame() + 1, newFrame);

    //tell the controller so we can add it to the model
    controller.newFrameAdded();

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
    //TODO:remove frame from widget at frame number
    delete ui->horizontalLayout->itemAt(0)->widget();
    delete ui->horizontalLayout->itemAt(0);
}
