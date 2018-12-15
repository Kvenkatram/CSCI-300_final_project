#ifndef CARD_H
#define CARD_H

#include <QColor>
#include <QGraphicsItem>

class card: public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    card(int x, int y, int did, int vp, QColor bonus, int cQ, int cR, int cE, int cS, int cD);
    card(); //defalut constructor
    QRectF boundingRect() const override;
    QRectF boundingCircle(int x, int y);
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_did() const { return did_; }
    int get_vp() const { return vp_; }
    int get_cD() const { return cD_; }
    int get_cE() const {return cE_; }
    int get_cR() const { return cR_; }
    int get_cS() const { return cS_; }
    int get_cQ() const { return cQ_; }
    QColor get_color() const { return bonus_; }

    int get_width() const { return width_; }
    int get_height() const { return height_; }

    void set_x(int x) { x_ = x; }
    void set_y(int y) { y_ = y; }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void cardClicked(card* c);
private:

    //top left corner
    int x_;
    int y_;
    //width and height
    int width_ = 157;
    int height_ = 177;

    int widthCircle_ = 30;
    // id and deck id
    int did_;
    //victory points
    int vp_;
    //cost
    int cD_;
    int cE_;
    int cR_;
    int cS_;
    int cQ_;
    QColor bonus_;

};

#endif // CARD_H
