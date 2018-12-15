#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "gamewindow.h"
#include <QPixmap>
#include <QResource>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    numpl_ = 0;
    numCPU_ = 0;


    QPixmap pix("://images/backgroundPic");


    ui->background->setPixmap(pix.scaled(1031,641));
    ui->background->lower();
}

login::~login()
{
    delete ui;
}

void login::on_numpl_activated(int index)
{
    numpl_ = index + 1;
}

void login::on_numcpu_activated(int index)
{
    numCPU_ = index;
}

void login::on_start_clicked()
{
    if (numpl_ >= numCPU_ && numpl_){
        this->hide();
        g_ = new GameWindow(this, numpl_, numCPU_);
        g_->show();
    }
}
