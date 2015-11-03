#include "graphicsscene.h"
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "qmath.h"

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::gray);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsRectItem* pixel = this->addRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 10, 10);
    pixel->setBrush(Qt::black);
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * me)
{
    QGraphicsScene::mouseReleaseEvent(me);
}

void GraphicsScene::clear(){
    QList <QGraphicsItem*> itemList = items();
    while(!itemList.isEmpty()){
        delete itemList.first();
        itemList = items();
    }
}
