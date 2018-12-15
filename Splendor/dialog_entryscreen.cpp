#include "dialog_entryscreen.h"
#include "ui_dialog_entryscreen.h"
#include <QPixmap>
#include "gamewindow.h"

Dialog_EntryScreen::Dialog_EntryScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_EntryScreen)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Vijay Venkatram/Documents/Qt/Splendor/images/backgroundPic");
    ui->introPic->setPixmap(pix.scaled(911,709));
    selection_ = 0; //initialize with no choice selected
}

Dialog_EntryScreen::~Dialog_EntryScreen()
{
    delete ui;
}

void Dialog_EntryScreen::on_startbutton_clicked()
{
    if (selection_){
        GameWindow *g = new GameWindow(this);
        hide();
        g->show();
    }
}

void Dialog_EntryScreen::on_comboBox_activated(int index)
{
    selection_ = index;
}

