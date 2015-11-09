#include "preview.h"
#include "ui_preview.h"
#include "canvas.h"

#include <QGraphicsView>
#include <QRect>

preview::preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preview)
{
    ui->setupUi(this);
}

preview::~preview()
{
    QGraphicsView* newFrame;
    newFrame = new QGraphicsView;

    Canvas* newScene;
    newScene = new Canvas(this);

    //set the scene and insert the graphics view into the horizontal frame holder
    newFrame->setScene(newScene);
    newFrame->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    //newFrame->setEnabled(false);

    //change the canvas in the main graphics view
    //QRect rcontent = graphicsView->contentsRect();
    //graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    //graphicsView->setScene(newScene);

    //TODO: add frame to the model

    delete ui;
}
