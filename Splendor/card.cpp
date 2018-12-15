#include "card.h"

#include <cstdlib>
#include <iostream>
#include <QtWidgets>


card::card(int x, int y, int did, int vp, QColor bonus, int cQ, int cR, int cE, int cS, int cD)
{
    x_ = x;
    y_ = y;
    did_ = did;
    vp_ = vp;
    bonus_ = bonus;
    cD_ = cD;
    cE_ = cE;
    cR_ = cR;
    cS_ = cS;
    cQ_ = cQ;
}


card::card(){
    cD_ = 1;
    cE_ = 0;
    cR_ = 0;
    cS_ = 0;
    cQ_ = 0;
}
/*the following are for the print function
 *
 */
QRectF card::boundingRect() const
{
    return QRectF(this->x_, this->y_, width_, height_);
}

QRectF card::boundingCircle(int x, int y){
    return QRectF(x,y,widthCircle_,widthCircle_);
}

/*QPainterPath card::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}
*/

void card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    /*
    QBrush b = painter->brush();
    painter->setBrush(QBrush(bonus_.dark(option->state & QStyle::State_Selected ? 120 : 100)));
    //draws rectangle with upper left corner and width and height
    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);

    */

    QColor brown(139,69,19);
    QRectF rec = boundingRect();
    QBrush bckgrnd(this->bonus_);
    //QBrush text(Qt::black);
    painter->fillRect(rec, bckgrnd);
    painter->drawRect(rec);
    //qDebug("test");
    QFont f;
    f.setBold(true);

    if (this->cQ_){
        QBrush quartz(brown);
        QPainterPath p1; // need to add a new path for each case
        p1.addEllipse(boundingCircle(this->x_ + 1, (this->y_) + 25));
        QPainterPath textp1;
        textp1.addText((this->x_+35), (this->y_)+40, f, QString::fromStdString("x" + std::to_string(this->cQ_)));
        painter->fillPath(p1,quartz);
        painter->fillPath(textp1,brown);
    }
    if (this->cR_){
        QBrush ruby(Qt::red);
        QPainterPath p2;
        p2.addEllipse(boundingCircle(this->x_ + 1, (this->y_) + 55));
        QPainterPath textp2;
        textp2.addText((this->x_+35), (this->y_)+70, f, QString::fromStdString("x" + std::to_string(this->cR_)));
        painter->fillPath(p2,ruby);
        painter->fillPath(textp2,ruby);
    }
    if (this->cE_){
        QBrush emerald(Qt::darkGreen);
        QPainterPath p3;
        p3.addEllipse(boundingCircle(this->x_ + 1, (this->y_) + 85));
        QPainterPath textp3;
        textp3.addText((this->x_+35), (this->y_)+100, f, QString::fromStdString("x" + std::to_string(this->cE_)));
        painter->fillPath(p3,emerald);
        painter->fillPath(textp3,emerald);
    }
    if (this->cS_){
        QBrush sapphire(Qt::blue);
        QPainterPath p4;
        p4.addEllipse(boundingCircle(this->x_ + 1, (this->y_) + 115));
        QPainterPath textp4;
        textp4.addText((this->x_+35), (this->y_)+130, f, QString::fromStdString("x" + std::to_string(this->cS_)));
        painter->fillPath(p4,sapphire);
        painter->fillPath(textp4,sapphire);
    }
    if (this->cD_){
        QBrush diamond(Qt::white);
        QPainterPath p5;
        p5.addEllipse(boundingCircle(this->x_ + 1, (this->y_) + 145));
        QPainterPath textp5;
        textp5.addText((this->x_+35), (this->y_)+160, f, QString::fromStdString("x" + std::to_string(this->cD_)));
        painter->fillPath(p5,diamond);
        painter->fillPath(textp5,diamond);
    }
    if (this->vp_){
        //QColor gold(255,223,0);
        QBrush b(Qt::yellow);
        QPainterPath p6;
        f.setPixelSize(30);
        p6.addText(this->x_ + 135, this->y_ + 30, f, QString::fromStdString(std::to_string(this->vp_)));
        painter->fillPath(p6,b);
    }


}

void card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event){
        if (cD_ + cE_ + cS_ + cQ_ + cR_){ // only emit signal if the card is a valid card and not an empty card for when the deck runs out
            emit cardClicked(this);
        }
    }
}


