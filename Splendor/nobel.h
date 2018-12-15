#ifndef NOBEL_H
#define NOBEL_H

#include "card.h"
#include <QColor>
#include <QGraphicsItem>

class nobel : public card
{
    Q_OBJECT
public:
    nobel(int x, int y,int cnD, int cnE, int cnR, int cnS, int cnQ, int nvp);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_nvp() const { return nvp_; }
    int get_ncD() const { return cnD_; }
    int get_ncE() const {return cnE_; }
    int get_ncR() const { return cnR_; }
    int get_ncS() const { return cnS_; }
    int get_ncQ() const { return cnQ_; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void nobelClicked(nobel* n);
private:
    //x and y
    int x_;
    int y_;
    //victory points
    int nvp_;
    //cost
    int cnD_;
    int cnE_;
    int cnR_;
    int cnS_;
    int cnQ_;
};

#endif // NOBEL_H
