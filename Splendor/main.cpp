#include "gamewindow.h"
#include <QApplication>
#include "dialog_entryscreen.h"
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login d;
    d.show();

    //GameWindow g;
    //g.show();

    return a.exec();
}
