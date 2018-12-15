#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "card.h"
#include "nobel.h"
#include <vector>

struct Player{
    int ID;
    int vp;
    bool AI;
    //number of gems
    //int gld;
    int rby;
    int emd;
    int dim;
    int sap;
    int qrt;

    //discounts
    //int dgld;
    int drby;
    int demd;
    int ddim;
    int dsap;
    int dqrt;

    //cumulative value

    int cD_;
    int cE_;
    int cR_;
    int cS_;
    int cQ_;

    //pointer to reserved card
    card *reserved;
};

enum class CurrentAction { StTurn, TK3S, TK3D, BYCRD, Reser, NBL, EndTurn, EndGame };

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, int pl = 0, int cpu = 0);
    ~GameWindow();

    void SetStaticPix(); //set static pictures
    void UpdatePlrLbl(Player* plr); //update player label
    void UpdateGemLbl(); //update global resources
    void PlayerDir(CurrentAction action, Player* plr); //updates the test field of who is going and what they can do
    void AIhandler(Player* plr);
    void initDeck1(); //initialize vector of card info
    void initDeck2();
    void initDeck3();
    void initNobels();

    nobel* drawNobels(int x, int y, std::string info);

    void setNobels();
    void initCards(); // initialze the board with cards

    card* cardFactory(int x, int y, int did, std::string info); //make cards
    void drawNewCard(int x, int y, int did);
    void cardPurchased(card *c);
    void nobelPurchased(nobel *n);

    bool gameWon(Player* p);


public slots:
    void cardClickedSlot(card *c);
    void nobelClickedSlot(nobel *n);

private slots:
    void on_same3_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_confirmButton_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_tk3d_clicked();

    void on_undoButton_clicked();

    void on_bycrd_clicked();

    void on_endTurn_clicked();

    void on_reser_clicked();

    void on_patron_clicked();

private:
    QGraphicsScene *scene; //for the game board
    QGraphicsScene *scene2; // got the reserved card
    QGraphicsScene *scene3; //for the nobels
    Ui::GameWindow *ui;

    //Player variables
    int numPl_; //number of players
    int numCPU_; // number of computer controlled players
    std::vector<Player*> players_; //player vector
    unsigned int turn_; //turn counter
    Player* currPl_; //pointer to current player
    Player* prevPl_; //pointer to previous player
    CurrentAction CurrAcc_; // current mode of the turn

    //gem variables for the checkboxes
    int buyQ;
    int buyE;
    int buyR;
    int buyS;
    int buyD;

    //global number if resources
    int gnumQ_;
    int gnumE_;
    int gnumR_;
    int gnumS_;
    int gnumD_;

    //holders of card info
    std::vector<std::string> deck1_;
    std::vector<std::string> deck2_;
    std::vector<std::string> deck3_;
    std::vector<std::string> nobels_;
};

#endif // GAMEWINDOW_H
