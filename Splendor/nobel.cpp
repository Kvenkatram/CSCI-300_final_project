#include "nobel.h"
#include <QPainter>
nobel::nobel(int x, int y,int cnD, int cnE, int cnR, int cnS, int cnQ, int nvp)
{
    x_ = x;
    y_ = y;
    cnD_ = cnD;
    cnE_ = cnE;
    cnR_ = cnR;
    cnS_ = cnS;
    cnQ_ = cnQ;
    nvp_ = nvp;

}

QRectF nobel::boundingRect() const
{
    return QRectF(this->x_, this->y_, get_width() , get_height() );
}

void nobel::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){

    Q_UNUSED(widget);

    QColor brown(139,69,19);
    QRectF rec = boundingRect();
    painter->drawRect(rec);

    QFont f;
    f.setBold(true);

    if (this->cnQ_){
        QBrush quartz(brown);
        QPainterPath p1; // need to add a new path for each case
        p1.addRect(boundingCircle(this->x_ + 1, (this->y_) + 25));
        QPainterPath textp1;
        textp1.addText((this->x_+35), (this->y_)+40, f, QString::fromStdString("x" + std::to_string(this->cnQ_)));
        painter->fillPath(p1,quartz);
        painter->fillPath(textp1,brown);
    }
    if (this->cnR_){
        QBrush ruby(Qt::red);
        QPainterPath p2;
        p2.addRect(boundingCircle(this->x_ + 1, (this->y_) + 55));
        QPainterPath textp2;
        textp2.addText((this->x_+35), (this->y_)+70, f, QString::fromStdString("x" + std::to_string(this->cnR_)));
        painter->fillPath(p2,ruby);
        painter->fillPath(textp2,ruby);
    }
    if (this->cnE_){
        QBrush emerald(Qt::darkGreen);
        QPainterPath p3;
        p3.addRect(boundingCircle(this->x_ + 1, (this->y_) + 85));
        QPainterPath textp3;
        textp3.addText((this->x_+35), (this->y_)+100, f, QString::fromStdString("x" + std::to_string(this->cnE_)));
        painter->fillPath(p3,emerald);
        painter->fillPath(textp3,emerald);
    }
    if (this->cnS_){
        QBrush sapphire(Qt::blue);
        QPainterPath p4;
        p4.addRect(boundingCircle(this->x_ + 1, (this->y_) + 115));
        QPainterPath textp4;
        textp4.addText((this->x_+35), (this->y_)+130, f, QString::fromStdString("x" + std::to_string(this->cnS_)));
        painter->fillPath(p4,sapphire);
        painter->fillPath(textp4,sapphire);
    }
    if (this->cnD_){
        QBrush diamond(Qt::white);
        QPainterPath p5;
        p5.addRect(boundingCircle(this->x_ + 1, (this->y_) + 145));
        QPainterPath textp5;
        textp5.addText((this->x_+35), (this->y_)+160, f, QString::fromStdString("x" + std::to_string(this->cnD_)));
        painter->fillPath(p5,diamond);
        painter->fillPath(textp5,diamond);
    }
    if (this->nvp_){
        QColor gold(255,223,0);
        QBrush b(gold);
        QPainterPath p6;
        f.setPixelSize(30);
        p6.addText(this->x_ + 135, this->y_ + 30, f, QString::fromStdString(std::to_string(this->nvp_)));
        painter->fillPath(p6,b);
    }


}


void nobel::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event){
        emit(nobelClicked(this));
    }
}

