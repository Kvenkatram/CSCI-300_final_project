#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "gamewindow.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_numpl_activated(int index);

    void on_numcpu_activated(int index);

    void on_start_clicked();

private:
    Ui::login *ui;

    GameWindow *g_;
    int numpl_;
    int numCPU_;
};

#endif // LOGIN_H
