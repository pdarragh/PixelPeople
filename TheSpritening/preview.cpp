#include "preview.h"
#include "ui_preview.h"
#include <iostream>;

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

void preview::updateFullPreview()
{
    // Updates to the current frame
    /*temp_frame = the_sprite.getFrame(temp_frame_int);
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
    temp_frame_int += 1;*/

    std::cout << "Timeout" << std::endl;
}
