#include <QObject>;
#include "canvas.h"
#include "preview.h"
#include "ui_preview.h"

preview::preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preview)
{
    ui->setupUi(this);

    full_timer = new QTimer(this);
    connect(full_timer, SIGNAL(timeout()), this, SLOT(updateFullPreview()));
}

preview::~preview()
{
    delete ui;
}

void preview::setController(Controller* controller)
{
    the_controller = controller;
    the_sprite = the_controller->getSprite();

    // Set the window size and prevent it from collapsing immediately
    ui->graphicsView->resize(the_sprite.getDimension(), the_sprite.getDimension());
    ui->graphicsView->setMinimumSize(the_sprite.getDimension(), the_sprite.getDimension());
    this->adjustSize();
}

void preview::setFPS(int value)
{
    //FPS = value;
    //int msec = (1000 / value);
    //int fps = value;
    full_timer->setInterval(1000 / value);
    //full_timer->setInterval(1000 / 3);
    full_timer->start();
}


void preview::updateFullPreview()
{
    // Updates to the current frame
    temp_frame = the_sprite.getFrame(temp_frame_int);
    QRect full_content = ui->graphicsView->contentsRect();
    int length_ = std::min(full_content.width(), full_content.height());
    full_scene = new Canvas(temp_frame_int, the_sprite.getDimension(), CanvasTypes::Preview, the_controller, this);

    // Sets the graphicsView_2 to display this new scene
    ui->graphicsView->setScene(full_scene);
    ui->graphicsView->setSceneRect(0, 0, full_content.width(), full_content.height());
    ui->graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    the_controller->populateCanvasFromFrame(full_scene, temp_frame_int);

    // Increment frames
    temp_frame_int += 1;

    // Make sure that if you reach the end, you go back to the beginning
    if (temp_frame_int == the_sprite.getFrameCount()) {
        temp_frame_int = 0;
    }
}


/*void preview::closeEvent(QCloseEvent *Event)
{
    QEvent* exitEvent = (QEvent*)Event;
    exitEvent->accept();
}*/
