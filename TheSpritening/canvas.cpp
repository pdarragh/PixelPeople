#include "canvas.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "qmath.h"


Canvas::Canvas(QObject *parent) :QGraphicsScene(parent)
{
   this->setBackgroundBrush(Qt::gray);
}

//void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
//{
//    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
//    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
//}

//void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
//{
//    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
//    QGraphicsScene::mouseMoveEvent(mouseEvent);
//}

//method that takes a qpoint dimension and color
void Canvas::doSomething(QPointF point, int x, int y, QColor color)
{

}

//array of pixels and a color and goes to do its thing
void Canvas::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();

        QGraphicsRectItem* pixel = this->addRect(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), 10, 10);
        m_points.push_back(mouseEvent->scenePos());
        pixel->setBrush(color);

    QGraphicsScene::mousePressEvent(mouseEvent);
}
void Canvas::checkIfNear(QPointF pointToCheck, QGraphicsSceneMouseEvent * mouseEvent)
{
    for(QList<QPointF>::iterator it = m_points.begin(); it != m_points.end(); it++)
    {
        if(pointToCheck.x() <= it->x()+20 && pointToCheck.y() <= it->y() + 5)
        {
            QGraphicsRectItem* pixel = this->addRect(it->x()+10, it->y(), 10, 10);
             pixel->setBrush(Qt::black);
        }
        else if(pointToCheck.x() <= it->x()-10)
        {

        }
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent * me)
{

    QGraphicsScene::mouseReleaseEvent(me);
}

void Canvas::drawBackground(QPainter *painter, const QRectF &rect)
{
    /*
    const int gridSize = 50;
    const int realLeft = static_cast<int>(std::floor(rect.left()));
    const int realRight = static_cast<int>(std::ceil(rect.right()));
    const int realTop = static_cast<int>(std::floor(rect.top()));
    const int realBottom = static_cast<int>(std::ceil(rect.bottom()));

    // Draw grid.
    const int firstLeftGridLine = realLeft - (realLeft % gridSize);
    const int firstTopGridLine = realTop - (realTop % gridSize);
    QVarLengthArray<QLine, 100> lines;

    for (qreal x = firstLeftGridLine; x <= realRight; x += gridSize)
        lines.append(QLine(x, realTop, x, realBottom));
    for (qreal y = firstTopGridLine; y <= realBottom; y += gridSize)
        lines.append(QLine(realLeft, y, realRight, y));

    painter->setPen(QPen(QColor(220, 220, 220), 0.0));
    painter->drawLines(lines.data(), lines.size());

    // Draw axes.
    painter->setPen(QPen(Qt::lightGray, 0.0));
    painter->drawLine(0, realTop, 0, realBottom);
    painter->drawLine(realLeft, 0, realRight, 0);*/
}

void Canvas::clear(){
    QList <QGraphicsItem*> itemList = items();
    while(!itemList.isEmpty()){
        delete itemList.first();
        itemList = items();
    }
}
