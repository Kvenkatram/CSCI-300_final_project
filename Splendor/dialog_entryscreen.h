#ifndef DIALOG_ENTRYSCREEN_H
#define DIALOG_ENTRYSCREEN_H

#include <QDialog>

namespace Ui {
class Dialog_EntryScreen;
}

class Dialog_EntryScreen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_EntryScreen(QWidget *parent = nullptr);
    ~Dialog_EntryScreen();

private:
    int selection_;

private slots:
    void on_startbutton_clicked();

    void on_comboBox_activated(int index);


private:
    Ui::Dialog_EntryScreen *ui;
};

#endif // DIALOG_ENTRYSCREEN_H
