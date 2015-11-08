#include "canvas.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "qmath.h"


Canvas::Canvas(QObject *parent) :QGraphicsScene(parent)
{
   this->setBackgroundBrush(Qt::gray);
   this->setSceneRect(100, 100, 50,50);

}

//method that takes a qpoint dimension and color
void Canvas::doSomething(QPointF point, int x, int y, QColor color)
{

}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    //print the position of the mouse click in the scene
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();

    //create the rectangle to draw
    QGraphicsRectItem* pixel = this->addRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 10, 10);
    m_points.push_back(mouseEvent->scenePos());

    //set brush and pen so that there is now black border around rectangle
    pixel->setBrush(color);
    pixel->setPen(color);

    //have to call this
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent * me)
{
    QGraphicsScene::mouseReleaseEvent(me);
}

void Canvas::clear(){

    QList <QGraphicsItem*> itemList = items();
    while(!itemList.isEmpty()){
        delete itemList.first();
        itemList = items();
    }
}
