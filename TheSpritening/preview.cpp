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
    std::cout << "Timeout" << std::endl;
}
