#include "preview.h"
#include "ui_preview.h"
#include "canvas.h"
#include <sstream>;
#include <iostream>;
#include <QObject>;

preview::preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preview)
{
    ui->setupUi(this);

    full_timer->setInterval(3000);

    connect(full_timer, SIGNAL(timeout()), this, SLOT(updateFullPreview()));

    full_timer->start();
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

/*void preview::setFrames(std::vector<Frame> allFrames)
{
    the_frames = allFrames;
}*/

void preview::updateFullPreview()
{
    // Updates to the current frame
    temp_frame = the_sprite.getFrame(temp_frame_int);
    QRect full_content = ui->graphicsView->contentsRect();
    int length = std::min(full_content.width(), full_content.height());
    full_scene = new Canvas(the_controller->getCurrentFrame(), length, false, the_controller, this);

    // Sets the graphicsView_2 to display this new scene
    ui->graphicsView->setScene(full_scene);
    ui->graphicsView->setSceneRect(0, 0, full_content.width(), full_content.height());

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

    std::cout << "Timeout" << std::endl;
}
