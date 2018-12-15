#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "card.h"
#include "nobel.h"
#include <QPixmap>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <QMessageBox>
#include <QDir>
#include <iostream>


GameWindow::GameWindow(QWidget *parent, int plr, int cpu) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    numPl_ = plr; //players give index of choice so increase by 1 to give number of plrs
    numCPU_ = cpu;
    //set global number of resources
    if ( numPl_ == 3){
        gnumQ_ = 5;
        gnumE_ = 5;
        gnumR_ = 5;
        gnumS_ = 5;
        gnumD_ = 5;
    }
    else if( numPl_ == 2){
        gnumQ_ = 4;
        gnumE_ = 4;
        gnumR_ = 4;
        gnumS_ = 4;
        gnumD_ = 4;
    }
    else{
        gnumQ_ = 7;
        gnumE_ = 7;
        gnumR_ = 7;
        gnumS_ = 7;
        gnumD_ = 7;
    }

    // scene is a pointer field of board and plot
    scene = new QGraphicsScene;
    scene2 = new QGraphicsScene;
    scene3 = new QGraphicsScene;

    // we need to set up the ui before we draw on our scene
    //ui for board
    QGraphicsView * view = ui->gameView;
    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());


    // ui for the reserved card;
    QGraphicsView * view2 = ui->resView;
    view2->setScene(scene2);
    view2->setSceneRect(0,0, view2->frameSize().width(),view2->frameSize().height());

    //ui for nobels
    QGraphicsView * view3 = ui->nobelView;
    view3->setScene(scene3);
    view3->setSceneRect(0,0, view3->frameSize().width(),view3->frameSize().height());

    // initialize the players
    for (int i =0; i < numPl_; i++){
        Player *plr = new Player;
        plr->ID = (i+1);
        plr->AI = false;
        plr->vp = 0;
        plr->dim = 0;
        plr->emd = 0;
        //plr->gld = 0;
        plr->qrt = 0;
        plr->rby = 0;
        plr->sap = 0;
        plr->ddim = 0;
        plr->demd = 0;
        //plr->dgld = 0;
        plr->dqrt = 0;
        plr->drby = 0;
        plr->dsap = 0;
        plr->cD_ = 0;
        plr->cE_ = 0;
        plr->cR_ = 0;
        plr->cS_ = 0;
        plr->cQ_ = 0;
        plr->reserved = nullptr;
        players_.push_back(plr);
        UpdatePlrLbl(plr);
    }

    //set up the bots
    for (int i = 0; i < numCPU_; i++){
        players_[i]->AI = true;
        UpdatePlrLbl(players_[i]);
    }

    //set turn and current player and set currrent action
    turn_ = 0;
    prevPl_ = nullptr;
    currPl_ = players_[turn_];
    CurrAcc_ = CurrentAction::StTurn;
    //set the static pictures and global resources labels
    SetStaticPix();
    UpdateGemLbl();

    //set up initial vaules for gem buying
    buyQ = 0;
    buyD = 0;
    buyE = 0;
    buyR = 0;
    buyS = 0;

    //set up cards
    initDeck1();
    initDeck2();
    initDeck3();
    initNobels();


    initCards();
    setNobels();

    //set up initial player dialog boxes
    PlayerDir(CurrAcc_,currPl_);
}

GameWindow::~GameWindow()
{
    delete ui;
}


/**
 * @brief GameWindow::SetStaticPix
 *
 * add all static images to the board
 */
void GameWindow::SetStaticPix(){
    //add static pix
        //the cards



    QPixmap stk1("://images/stck1Pix.JPG");
    QPixmap stk2("://images/stck2Pix.JPG");
    QPixmap stk3("://images/stck3Pix.JPG");
        //the gems
    //QPixmap gPix("C:/Users/Vijay Venkatram/Documents/Qt/Splendor/goldPix");
    QPixmap rPix("://images/ruby");
    QPixmap sPix("://images/sapphire");
    QPixmap dPix("://images/diamond");
    QPixmap ePix("://images/emerald");
    QPixmap qPix("://images/quartz");
        //background
    QPixmap bck("://images/marble");

    ui->backgoundPix->setPixmap(bck.scaled(1521,901));
    ui->backgoundPix->lower();
    ui->stck1Pix->setPixmap(stk1.scaled(149,172));
    ui->stck2Pix->setPixmap(stk2.scaled(149,172));
    ui->stck3Pix->setPixmap(stk3.scaled(149,172));
    //ui->Pixgold->setPixmap(gPix.scaled(89,64));
    ui->Pixruby->setPixmap(rPix.scaled(89,64));
    ui->Pixsaphire->setPixmap(sPix.scaled(89,64));
    ui->Pixdiamond->setPixmap(dPix.scaled(89,64));
    ui->Pixemerald->setPixmap(ePix.scaled(89,64));
    ui->Pixquarts->setPixmap(qPix.scaled(89,64));
}

/**
 * @brief GameWindow::UpdatePlrLbl
 * @param plr
 *
 * updates the labels of the player's names and VP
 * update when changes in vp
 */
void GameWindow::UpdatePlrLbl(Player *plr){
    int VP = plr->vp;
    int id = plr->ID;
    
    std::string vp = "VP " + std::to_string(VP);
    std::string name = "Player " + std::to_string(id);
    if (plr->AI){
        name = name + " (CPU)";
    }

    QString qname = QString::fromStdString(name);
    QString qvp = QString::fromStdString(vp);
    if (id == 1){
        ui->pl1vp->setText(qvp);
        ui->pl1->setText(qname);
    }
    else if (id == 2){
        ui->pl2vp->setText(qvp);
        ui->pl2->setText(qname);
    }
    else if (id == 3){
        ui->pl3vp->setText(qvp);
        ui->pl3->setText(qname);
    }
    else {
        ui->pl4vp->setText(qvp);
        ui->pl4->setText(qname);
    }
}


/**
 * @brief GameWindow::UpdateGemLbl
 *
 * update global number of resources
 */
void GameWindow::UpdateGemLbl(){

    ui->gnumD->setNum(gnumD_);
    ui->gnumE->setNum(gnumE_);
    ui->gnumrby->setNum(gnumR_);
    ui->gnumS->setNum(gnumS_);
    ui->gnumQ->setNum(gnumQ_);
}

/**
 * @brief GameWindow::PlayerDir
 * @param x
 *
 * manages the player info text boxes
 * central hub of the game
 * when a player clicks a button this function updates the instructions on the screene
 */
void GameWindow::PlayerDir(CurrentAction action, Player* plr){

    std::string dir;
    QString qdir;
    QPixmap pix;
    if (action == CurrentAction::StTurn){ // start of turn


        if (plr->AI){ // if it is an CPU call the cpu handler and return
            AIhandler(plr);
            return;
        }

        int VP = plr->vp;
        int id = plr->ID;
        std::string s = "Player " + std::to_string(id) + "  VP: " + std::to_string(VP);
        QString qs = QString::fromStdString(s);

        dir = "Please select an option";
        qdir = QString::fromStdString(dir);

        QPixmap pix("://images/your_turn");
        ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));

        ui->Plrturn->setText(qs);
        ui->plrDirection->setText(qdir);
        ui->numQ->setNum(plr->qrt);
        ui->numR->setNum(plr->rby);
        ui->numD->setNum(plr->dim);
        ui->numE->setNum(plr->emd);
        ui->numS->setNum(plr->sap);
        ui->disD->setNum(plr->ddim);
        ui->disE->setNum(plr->demd);
        ui->disQ->setNum(plr->dqrt);
        ui->disR->setNum(plr->drby);
        ui->disS->setNum(plr->dsap);
        ui->cumD->setNum(plr->cD_);
        ui->cumR->setNum(plr->cR_);
        ui->cumE->setNum(plr->cE_);
        ui->cumS->setNum(plr->cS_);
        ui->cumQ->setNum(plr->cQ_);

        if (prevPl_){ // remove the previous image from the reserved card spot
            if (prevPl_->reserved != nullptr){
                scene2->removeItem(prevPl_->reserved);
            }
        }
        if (currPl_->reserved != nullptr){ // display card in reserved card slot
            scene2->addItem(currPl_->reserved);
        }

    }
    else if( action == CurrentAction::TK3S){ // take 3 of the same gem
        QPixmap pix("://images/3Same");
        ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));
        dir = "Select a Gem";
        qdir = QString::fromStdString(dir);
        ui->plrDirection->setText(qdir);
    }
    else if( action == CurrentAction::TK3D){ // take 3 different games
        QPixmap pix("://images/3Diff");
       ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));
        dir = "Select 3 Gems";
        qdir = QString::fromStdString(dir);
        ui->plrDirection->setText(qdir);
    }
    else if( action == CurrentAction::EndTurn){ // end of the turn
        QPixmap pix("://images/endturn");
        ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));
        dir = "Turn Compleated. Click End Turn";
        qdir = QString::fromStdString(dir);

        int VP = plr->vp;
        int id = plr->ID;
        std::string s = "Player " + std::to_string(id) + "  VP: " + std::to_string(VP);
        QString qs = QString::fromStdString(s);

        ui->Plrturn->setText(qs);
        ui->plrDirection->setText(qdir);

        ui->numQ->setNum(plr->qrt);
        ui->numR->setNum(plr->rby);
        ui->numD->setNum(plr->dim);
        ui->numE->setNum(plr->emd);
        ui->numS->setNum(plr->sap);
        ui->disD->setNum(plr->ddim);
        ui->disE->setNum(plr->demd);
        ui->disQ->setNum(plr->dqrt);
        ui->disR->setNum(plr->drby);
        ui->disS->setNum(plr->dsap);
        ui->cumD->setNum(plr->cD_);
        ui->cumR->setNum(plr->cR_);
        ui->cumE->setNum(plr->cE_);
        ui->cumS->setNum(plr->cS_);
        ui->cumQ->setNum(plr->cQ_);

        if (plr->reserved != nullptr){
            scene2->addItem(plr->reserved);
        }
    }
    else if(action == CurrentAction::BYCRD){ // buy a card
        QPixmap pix("://images/pickcard");
        ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));
        dir = "Pick a Card to Buy";
        qdir = QString::fromStdString(dir);

        ui->plrDirection->setText(qdir);
    }
    else if(action == CurrentAction::Reser){ // reserve a card
        QPixmap pix("://images/reserve");
        ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));
        dir = "Pick a Card to Reserve";
        qdir = QString::fromStdString(dir);
        ui->plrDirection->setText(qdir);
    }
    else if(action == CurrentAction::NBL){ //impress a noble
        QPixmap pix("://images/noble");
        ui->CurrAccPic->setPixmap(pix.scaled(201,131,Qt::KeepAspectRatio));
        dir = "Pick a Nobel";
        qdir = QString::fromStdString(dir);
        ui->plrDirection->setText(qdir);
    }
    else if(action == CurrentAction::EndGame){ // end the game
        int VP = plr->vp;
        int id = plr->ID;
        std::string s = "Player " + std::to_string(id) + "  VP: " + std::to_string(VP);
        QString qs = QString::fromStdString(s);
        ui->Plrturn->setText(qs);

        std::string s2 = "Player " + std::to_string(id) + " Won!";
        QString qs2 = QString::fromStdString(s2);
        QMessageBox::about(this,"GM Says", qs2);
        this->close();

        //could instantiate a new instance of login-in to reset the game
    }
}


/**
 * @brief GameWindow::on_same3_clicked
 *
 * slot for when take 3 of the same is clicked
 * update current action and call playerhandler
 */
void GameWindow::on_same3_clicked()
{

    if ( CurrAcc_ == CurrentAction::StTurn ){
        CurrAcc_ = CurrentAction::TK3S;
        PlayerDir(CurrAcc_, currPl_);
    }
}



/**
 * @brief GameWindow::on_tk3d_clicked
 *
 * slot for when take 3 different is clicked
 */

void GameWindow::on_tk3d_clicked()
{
    if( CurrAcc_ == CurrentAction::StTurn){
        CurrAcc_ = CurrentAction::TK3D;
        PlayerDir(CurrAcc_,currPl_);
    }
}


/**
 * @brief GameWindow::on_bycrd_clicked
 *
 * when bycrd button is clicked then need to make sure if they can buy the card
 * give bonus and vp if bought
 * give message if unable to buy
 */
void GameWindow::on_bycrd_clicked()
{
    if (CurrAcc_ == CurrentAction::StTurn){
        CurrAcc_ = CurrentAction::BYCRD;
        PlayerDir(CurrAcc_, currPl_);
    }
}


/**
 * @brief GameWindow::on_endTurn_clicked
 *
 * when clicked end the turn
 * set the current player to the next player in the list
 * reset fields
 */
void GameWindow::on_endTurn_clicked()
{

    if (gameWon(currPl_)){ // if vp = 15 then end the game
        CurrAcc_ = CurrentAction::EndGame;
        PlayerDir(CurrAcc_, currPl_);
    }
    else{
        prevPl_ = currPl_;
        turn_++;
        if ( turn_ == numPl_ ){ //turn is indexed where plr 1 is turn = 0
            turn_ = 0;
        }
        currPl_ = players_[turn_];
        CurrAcc_ = CurrentAction::StTurn;
        std::string i = "Player " + std::to_string(currPl_->ID) + " It's Now Your Turn!";
        QString qi = QString::fromStdString(i);
        QMessageBox::about(this,"GM Says", qi);
        PlayerDir(CurrAcc_,currPl_);

    }

}

/**
 * @brief GameWindow::on_reser_clicked
 *
 * when a crad is reserved set new state and send instruction to player dir
 */
void GameWindow::on_reser_clicked()
{
    if (CurrAcc_ == CurrentAction::StTurn){
        if(currPl_->reserved == nullptr){
            CurrAcc_ = CurrentAction::Reser;
            PlayerDir(CurrAcc_, currPl_);
        }
        else{
            QMessageBox::about(this,"GM", "Already have a reserved card");
        }
    }
}


/**
 * @brief GameWindow::on_patron_clicked
 *
 * allow player to try and impress a nobel
 * sets curracc to NBL
 */
void GameWindow::on_patron_clicked()
{
    if (CurrAcc_ == CurrentAction::StTurn){
        CurrAcc_ = CurrentAction::NBL;
        PlayerDir(CurrAcc_, currPl_);
    }
}


/**
 * @brief GameWindow::on_checkBox_stateChanged
 * @param arg1
 *
 * slot of quartz checkbox
 */
void GameWindow::on_checkBox_stateChanged(int arg1)
{
    if (CurrAcc_ == CurrentAction::TK3S || CurrAcc_ == CurrentAction::TK3D){
        buyQ = arg1;
    }
}


/**
 * @brief GameWindow::on_checkBox_2_stateChanged
 * @param arg1
 *
 *slot of ruby
 */
void GameWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (CurrAcc_ == CurrentAction::TK3S || CurrAcc_ == CurrentAction::TK3D){
        buyR = arg1;
    }
}


/**
 * @brief GameWindow::on_checkBox_3_stateChanged
 * @param arg1
 *
 * slot of emerald checkbox
 */
void GameWindow::on_checkBox_3_stateChanged(int arg1)
{
    if (CurrAcc_ == CurrentAction::TK3S || CurrAcc_ == CurrentAction::TK3D){
        buyE = arg1;
    }
}


/**
 * @brief GameWindow::on_checkBox_4_stateChanged
 * @param arg1
 *
 * slot of Sapphire checkbox
 */
void GameWindow::on_checkBox_4_stateChanged(int arg1)
{
    if (CurrAcc_ == CurrentAction::TK3S || CurrAcc_ == CurrentAction::TK3D){
        buyS = arg1;
    }
}


/**
 * @brief GameWindow::on_checkBox_5_stateChanged
 * @param arg1
 *
 * slot of diamond checkbox
 */
void GameWindow::on_checkBox_5_stateChanged(int arg1)
{
    if (CurrAcc_ == CurrentAction::TK3S || CurrAcc_ == CurrentAction::TK3D){
        buyD = arg1;
    }
}


/**
 * @brief GameWindow::on_confirmButton_clicked
 *
 * used to buy gems and manage the check boxes
 * only runs when CurrAcc is either TK3S or TK3D
 */
void GameWindow::on_confirmButton_clicked()
{
    bool valid = false;
    if (CurrAcc_ == CurrentAction::TK3S){
        if ((buyD+buyE+buyQ+buyR+buyS) == 2){ //if only one selected should equal 2
            valid = true;
            if (buyD){
                if (gnumD_ >= 3){ // need at least 3 to take
                    currPl_->dim = currPl_->dim + 3;
                    currPl_->cD_ += 3;
                    gnumD_ -= 3;
                }
                else{
                    valid = false;
                }
            }
            else if(buyE){
                if (gnumE_ >= 3){ // need at least 3 to take
                     currPl_->emd = currPl_->emd + 3;
                     currPl_->cE_ += 3;
                     gnumE_ -= 3;
                }
                else{
                    valid = false;
                }
            }
            else if(buyQ){
                if (gnumQ_ >= 3){ // need at least 3 to take
                     currPl_->qrt = currPl_->qrt + 3;
                     currPl_->cQ_ += 3;
                     gnumQ_ -= 3;
                }
                else{
                    valid = false;
                }
            }
            else if(buyR){
                if (gnumR_ >= 3){ // need at least 3 to take
                     currPl_->rby = currPl_->rby + 3;
                     currPl_->cQ_ += 3;
                     gnumR_ -= 3;
                }
                else{
                    valid = false;
                }
            }
            else{
                if (gnumS_ >= 3){ // need at least 3 to take
                     currPl_->sap = currPl_->sap + 3;
                     currPl_->cS_ += 3;
                     gnumS_ -= 3;
                }
                else{
                    valid = false;
                }
            }
        }
    }
    else if(CurrAcc_ == CurrentAction::TK3D){
        if ((buyD+buyE+buyQ+buyR+buyS) == 6){ // if 3 selected then should equal 6
            valid = true;
            if (buyD){
                if (gnumD_ < 1){ // need at least 1 to take
                    valid = false;
                }
            }
            if(buyE){
                if (gnumE_ < 1){ // need at least 1 to take
                    valid = false;
                }
            }
            if(buyQ){
                if (gnumQ_ < 1){ // need at least 1 to take
                    valid = false;
                }
            }
            if(buyR){
                if (gnumR_ < 1){ // need at least 1 to take
                    valid = false;
                }
            }
            if(buyS){
                if (gnumS_ < 1){ // need at least 1 to take
                    valid = false;
                }
            }
        }
    }
    //reset and print end turn instructions and give resources
    if (valid){
        if (CurrAcc_ == CurrentAction::TK3D){
            if (buyD){
                currPl_->cD_ += 1;
                gnumD_ -= 1;
                currPl_->dim += 1;
            }
            if (buyE){
                currPl_->cE_ += 1;
                gnumE_ -= 1;
                currPl_->emd += 1;
            }
            if (buyR){
                currPl_->cR_ += 1;
                gnumR_ -= 1;
                currPl_->rby += 1;
            }
            if (buyS){
                currPl_->cS_ += 1;
                gnumS_ -= 1;
                currPl_->sap += 1;
            }
            if (buyQ){
                currPl_->cQ_ += 1;
                gnumQ_ -= 1;
                currPl_->qrt += 1;
            }
        }
        ui->checkBox->setCheckState(Qt::CheckState(false));
        ui->checkBox_2->setCheckState(Qt::CheckState(false));
        ui->checkBox_3->setCheckState(Qt::CheckState(false));
        ui->checkBox_4->setCheckState(Qt::CheckState(false));
        ui->checkBox_5->setCheckState(Qt::CheckState(false));
        buyD = 0;
        buyE = 0;
        buyQ = 0;
        buyR = 0;
        buyS = 0;
        UpdateGemLbl();
        CurrAcc_ = CurrentAction::EndTurn;
        PlayerDir(CurrAcc_, currPl_);
    }
    else{
        QMessageBox::about(this, "GM Says", "Invalid Selection");
    }
}


/**
 * @brief GameWindow::on_undoButton_clicked
 *
 * when undobutton is clicked set gamestate back to start of turn and uncheck all boxes
 */
void GameWindow::on_undoButton_clicked()
{
    if (CurrAcc_ != CurrentAction::StTurn && CurrAcc_ != CurrentAction::EndTurn){
        ui->checkBox->setCheckState(Qt::CheckState(false));
        ui->checkBox_2->setCheckState(Qt::CheckState(false));
        ui->checkBox_3->setCheckState(Qt::CheckState(false));
        ui->checkBox_4->setCheckState(Qt::CheckState(false));
        ui->checkBox_5->setCheckState(Qt::CheckState(false));
        CurrAcc_ = CurrentAction::StTurn;
        PlayerDir(CurrAcc_,currPl_);
    }
}


/**
 * @brief GameWindow::initCards
 *
 * set up the inital board with 12 cards
 * make calls to cardfactory to make new cards for each row from the different decks
 */
void GameWindow::initCards(){

    srand(time(0));

    // dont need all the loops can be done in one loop
    //seperated for debugging will consolidate later

    for (int i = 0; i < 4; i++){ //deck 1
        unsigned int index = rand() % (deck1_.size()+1);
        card *c = cardFactory(i*157,0,1,deck1_[index]);
        deck1_.erase(deck1_.begin() + (int)index);
        //std::cout << deck1_.size() << std::endl;
        scene->addItem(c);
        connect(c,&card::cardClicked, this, &GameWindow::cardClickedSlot);
    }
    for (int i = 0; i < 4; i++){ // deck 2
        unsigned int index = rand() % (deck2_.size()+1);
        card *c = cardFactory(i*157,177,2,deck2_[index]);
        deck2_.erase(deck2_.begin() + (int)index);
        //std::cout << deck1_.size() << std::endl;
        scene->addItem(c);
        connect(c,&card::cardClicked, this, &GameWindow::cardClickedSlot);
    }
    for (int i =0; i < 4; i++){ // deck3
        unsigned int index = rand() % (deck3_.size()+1);
        card *c = cardFactory(i*157,354,3,deck3_[index]);
        deck3_.erase(deck3_.begin() + (int)index);
        //std::cout << deck1_.size() << std::endl;
        scene->addItem(c);
        connect(c,&card::cardClicked, this, &GameWindow::cardClickedSlot);
    }

    //scene->addItem(cardFactory(0,0,1,"030000w"));
}


/**
 * @brief GameWindow::cardFactory
 * @param x
 * @param y
 * @param did
 * @param info
 * @return
 *
 * read in the string coding the properties of the card
 * extract info and call card constructor
 */

card* GameWindow::cardFactory(int x, int y, int did, std::string info){
//int x, int y, int did, int vp, QColor bonus, int cQ, int cR, int cE, int cS, int cD

    QColor white(229,229,229);
    QColor ruby(255,102,102);
    QColor brown(244,164,96);
    QColor blue(0,191,255);
    QColor green(0,250,154);

    int w = (info[0]) - ('0');
    int b = (info[1]) - ('0');
    int g = (info[2]) - ('0');
    int r = (info[3]) - ('0');
    int q = (info[4]) - ('0');
    int v = (info[5]) - ('0');


    char color = info[6];

    QColor qcolor;

    card* cd;

    if (color == 'w' ) {
        qcolor = white;
    }
    else if(color == 'b') {
        qcolor = blue;
    }
    else if(color == 'q') {
        qcolor = brown;
    }
    else if (color == 'g') {
        qcolor = green;
    }
    else{
        qcolor = ruby;
    }

    cd = new card(x, y, did, v, qcolor, q, r, g, b, w);


    return cd;
}


/**
 * @brief GameWindow::drawNewCard
 * @param x
 * @param y
 * @param did
 *
 * draw a new card and add it to the board
 * delete entry to the card deck list
 */
void GameWindow::drawNewCard(int x, int y, int did){
    //qDebug("drew a card");
    srand(time(0));
    if (did == 1){
        if (deck1_.size()){
            unsigned int index = rand() % (deck1_.size()+1);
            card *c = cardFactory(x,y,1,deck1_[index]);
            deck1_.erase(deck1_.begin() + (int)index );
            //std::cout << deck1_.size() << std::endl;
            scene->addItem(c);
            connect(c,&card::cardClicked, this, &GameWindow::cardClickedSlot);
        }
        else{
            //qDebug("test");
            card *c = cardFactory(x,y,1,"000000w");
            scene->addItem(c);
        }
    }
    if (did == 2){
        if (deck2_.size()){
            unsigned int index = rand() % (deck2_.size()+1);
            card *c = cardFactory(x,y,2,deck2_[index]);
            deck2_.erase(deck2_.begin() + (int)index );
            //std::cout << deck1_.size() << std::endl;
            scene->addItem(c);
            connect(c,&card::cardClicked, this, &GameWindow::cardClickedSlot);
        }
        else{
            //qDebug("test");
            card *c = cardFactory(x,y,2,"000000w");
            scene->addItem(c);
        }
    }
    if (did == 3){
        if (deck3_.size()){
            unsigned int index = rand() % (deck3_.size()+1);
            card *c = cardFactory(x,y,3,deck3_[index]);
            deck3_.erase(deck3_.begin() + (int)index );
            //std::cout << deck1_.size() << std::endl;
            scene->addItem(c);
            connect(c,&card::cardClicked, this, &GameWindow::cardClickedSlot);
        }
        else{
            //qDebug("test");
            card *c = cardFactory(x,y,3,"000000w");
            scene->addItem(c);
        }
    }
}

/**
 * @brief GameWindow::cardPurchased
 * @param c
 *
 * draw a new card at same location of card pointer
 * update player vp and reasource points
 */

void GameWindow::cardPurchased(card *c){

    QColor white(229,229,229);
    QColor ruby(255,102,102);
    QColor brown(244,164,96);
    QColor blue(0,191,255);
    QColor green(0,250,154);

    int dcost = 0;
    int ecost = 0;
    int rcost = 0;
    int scost = 0;
    int qcost = 0;

    //find the cost of the card with discounts
    if (c->get_cD()){
        dcost = c->get_cD() - currPl_->ddim;
        if (dcost < 0){
            dcost = 0;
        }
    }
    if (c->get_cE()){
        ecost = c->get_cE() - currPl_->demd;
        if (ecost < 0){
            ecost = 0;
        }
    }
    if  (c->get_cR()){
        rcost = c->get_cR() - currPl_->drby;
        if (rcost < 0){
            rcost = 0;
        }
    }
    if (c->get_cS()){
        scost = c->get_cS() - currPl_->dsap;
        if (scost < 0){
            scost = 0;
        }
    }
    if (c->get_cQ()){
        qcost = c->get_cQ() - currPl_->dqrt;
        if (qcost < 0){
            qcost = 0;
        }
    }



    currPl_->dim = currPl_->dim - dcost;
    currPl_->emd = currPl_->emd - ecost;
    currPl_->rby = currPl_->rby - rcost;
    currPl_->sap = currPl_->sap - scost;
    currPl_->qrt = currPl_->qrt - qcost;
    currPl_->vp = currPl_->vp + c->get_vp();

    gnumD_ = gnumD_ + dcost;
    gnumE_ = gnumE_ + ecost;
    gnumQ_ = gnumQ_ + qcost;
    gnumR_ = gnumR_ + rcost;
    gnumS_ = gnumS_ + scost;

    UpdateGemLbl();

    QColor color = c->get_color();
    if (color == brown ){
        currPl_->dqrt++;
    }
    else if(color == white){
        currPl_->ddim++;
    }
    else if(color == green){
        currPl_->demd++;
    }
    else if(color == blue){
        currPl_->dsap++;
    }
    else{
        currPl_->drby++;
    }

    //free card object
    delete(c);

    std::string cost = "Cost of card with discounts is " + std::to_string(dcost) + " Diamonds, " + std::to_string(ecost) + " Emeralds, " + std::to_string(rcost) + " Rubies, " + std::to_string(scost) + " Sapphires, " + std::to_string(qcost) + " and Quartz ";
    QString Qcost = QString::fromStdString(cost);
    QMessageBox::about(this, "GM Says", Qcost);
}


/**
 * @brief GameWindow::cardClickedSlot
 * @param c
 *
 * when a card is clicked
 * check to see if the player clicking as the resources to purchase
 */
void GameWindow::cardClickedSlot(card *c){
    if (CurrAcc_ == CurrentAction::BYCRD){
        bool valid = true;
        if ((currPl_->dim + currPl_->ddim) < c->get_cD()){
            valid = false;
        }
        if ((currPl_->emd + currPl_->demd) < c->get_cE()){
            valid = false;
        }
        if ((currPl_->rby + currPl_->drby) < c->get_cR()){
            valid = false;
        }
        if ((currPl_->sap + currPl_->dsap) < c->get_cS()){
            valid = false;
        }
        if ((currPl_->qrt + currPl_->dqrt) < c->get_cQ()){
            valid = false;
        }
        if (valid){ // can buy card
            if (currPl_->reserved == c){
                scene2->removeItem(c);
                currPl_->reserved = nullptr;
            }
            else{
                drawNewCard(c->get_x(), c->get_y(), c->get_did());
            }
            cardPurchased(c);
            UpdatePlrLbl(currPl_);
            QMessageBox::about(this, "GM", "Card Purchased. Resources Deducted");
            CurrAcc_ = CurrentAction::EndTurn;
            PlayerDir(CurrAcc_, currPl_);
        }
        else{
            QMessageBox::about(this, "GM", "Not enough Resources");
        }
    }
    else if(CurrAcc_ == CurrentAction::Reser){
        scene->removeItem(c);
        drawNewCard(c->get_x(),c->get_y(),c->get_did());
        CurrAcc_ = CurrentAction::EndTurn;
        c->set_x(0);
        c->set_y(0);
        currPl_->reserved = c;
        PlayerDir(CurrAcc_, currPl_);
    }
}


/**
 * @brief GameWindow::nobelPurchased
 * @param n
 *
 * give vp to player
 * delete nobel card from the board
 */
void GameWindow::nobelPurchased(nobel *n){
    currPl_->vp = currPl_->vp + n->get_nvp();

    QMessageBox::about(this, "GM Says", "Nobel was Impressed, VP Awarded");
    scene3->removeItem(n);
    delete(n);
}

/**
 * @brief GameWindow::nobelClickedSlot
 * @param n
 *
 * when a nobel is clicked while in get patron mode
 * check to see if meet requirments
 * give vp to player
 * or send message saying not good enough
 */
void GameWindow::nobelClickedSlot(nobel *n){
    if (CurrAcc_ == CurrentAction::NBL){
        bool valid = true;
        int Q = n->get_ncQ();
        int E = n->get_ncE();
        int R = n->get_ncR();
        int S = n->get_ncS();
        int D = n->get_ncD();

        if (Q){
            if (currPl_->dqrt < Q ){
                valid = false;
            }
        }
        if (E){
            if (currPl_->demd < E ){
                valid = false;
            }
        }
        if (R){
            if (currPl_->drby < R ){
                valid = false;
            }
        }
        if (S){
            if (currPl_->dsap < S ){
                valid = false;
            }
        }
        if (D){
            if (currPl_->ddim < D ){
                valid = false;
            }
        }

        if(valid){
            nobelPurchased(n);
            CurrAcc_ = CurrentAction::EndTurn;
            PlayerDir(CurrAcc_,currPl_);
        }
        else{
            QMessageBox::about(this, "GM Says", "Not Enough Resource Cards to Impress Patron");
        }

    }
}


/**
 * @brief GameWindow::gameWon
 * @param p
 * @return
 *
 * if the game is won
 * return true
 * is called in the "on end turn botton clicked" method
 */

bool GameWindow::gameWon(Player *p){

    if (p->vp >= 15){ // end game when have 15 vp
        return true;
    }

    return false;
}

void GameWindow::initDeck1(){

    std::string c1 = "030000w";
    std::string c2 = "000210w";
    std::string c3 = "011110w";
    std::string c4 = "020020w";
    std::string c5 = "004001w";
    std::string c6 = "012110w";
    std::string c7 = "022010w";
    std::string c8 = "310010w";
    std::string c9 = "100020b";
    std::string c10 = "000030b";
    std::string c11 = "101110b";
    std::string c12 = "002020b";
    std::string c13 = "000401b";
    std::string c14 = "101210b";
    std::string c15 = "102200b";
    std::string c16 = "013100b";
    std::string c17 = "210000g";
    std::string c18 = "000300g";
    std::string c19 = "110110g";
    std::string c20 = "020200g";
    std::string c21 = "000041g";
    std::string c22 = "110120g";
    std::string c23 = "010220g";
    std::string c24 = "131000g";
    std::string c25 = "021000r";
    std::string c26 = "300000r";
    std::string c27 = "111010r";
    std::string c28 = "200200r";
    std::string c29 = "400001r";
    std::string c30 = "211010r";
    std::string c31 = "201020r";
    std::string c32 = "100130r";
    std::string c33 = "002100q";
    std::string c34 = "003000q";
    std::string c35 = "111100q";
    std::string c36 = "202000q";
    std::string c37 = "040001q";
    std::string c38 = "121100q";
    std::string c39 = "220100q";
    std::string c40 = "001310q";
    deck1_.push_back(c1);
    deck1_.push_back(c2);
    deck1_.push_back(c3);
    deck1_.push_back(c4);
    deck1_.push_back(c5);
    deck1_.push_back(c6);
    deck1_.push_back(c7);
    deck1_.push_back(c8);
    deck1_.push_back(c9);
    deck1_.push_back(c10);
    deck1_.push_back(c11);
    deck1_.push_back(c12);
    deck1_.push_back(c13);
    deck1_.push_back(c14);
    deck1_.push_back(c15);
    deck1_.push_back(c16);
    deck1_.push_back(c17);
    deck1_.push_back(c18);
    deck1_.push_back(c19);
    deck1_.push_back(c20);
    deck1_.push_back(c21);
    deck1_.push_back(c22);
    deck1_.push_back(c23);
    deck1_.push_back(c24);
    deck1_.push_back(c25);
    deck1_.push_back(c26);
    deck1_.push_back(c27);
    deck1_.push_back(c28);
    deck1_.push_back(c29);
    deck1_.push_back(c30);
    deck1_.push_back(c31);
    deck1_.push_back(c32);
    deck1_.push_back(c33);
    deck1_.push_back(c34);
    deck1_.push_back(c35);
    deck1_.push_back(c36);
    deck1_.push_back(c37);
    deck1_.push_back(c38);
    deck1_.push_back(c39);
    deck1_.push_back(c40);
}

void GameWindow::initDeck2(){

    std::string c1 = "000502w";
    std::string c2 = "600003w";
    std::string c3 = "003221w";
    std::string c4 = "001422w";
    std::string c5 = "230301w";
    std::string c6 = "000532w";
    std::string c7 = "005002b";
    std::string c8 = "006003b";
    std::string c9 = "230021b";
    std::string c10 = "302301b";
    std::string c11 = "420012b";
    std::string c12 = "053002b";
    std::string c13 = "005002g";
    std::string c14 = "006003g";
    std::string c15 = "230021g";
    std::string c16 = "302301g";
    std::string c17 = "420012g";
    std::string c18 = "053002g";
    std::string c19 = "000052r";
    std::string c20 = "000603r";
    std::string c21 = "200231r";
    std::string c22 = "142002r";
    std::string c23 = "142002r";
    std::string c24 = "030231r";
    std::string c25 = "300052r";
    std::string c26 = "000052q";
    std::string c27 = "000063q";
    std::string c28 = "322001q";
    std::string c29 = "014202q";
    std::string c30 = "303021q";
    std::string c31 = "005302q";
    deck2_.push_back(c1);
    deck2_.push_back(c2);
    deck2_.push_back(c3);
    deck2_.push_back(c4);
    deck2_.push_back(c5);
    deck2_.push_back(c6);
    deck2_.push_back(c7);
    deck2_.push_back(c8);
    deck2_.push_back(c9);
    deck2_.push_back(c10);
    deck2_.push_back(c11);
    deck2_.push_back(c12);
    deck2_.push_back(c13);
    deck2_.push_back(c14);
    deck2_.push_back(c15);
    deck2_.push_back(c16);
    deck2_.push_back(c17);
    deck2_.push_back(c18);
    deck2_.push_back(c19);
    deck2_.push_back(c20);
    deck2_.push_back(c21);
    deck2_.push_back(c22);
    deck2_.push_back(c23);
    deck2_.push_back(c24);
    deck2_.push_back(c25);
    deck2_.push_back(c26);
    deck2_.push_back(c27);
    deck2_.push_back(c28);
    deck2_.push_back(c29);
    deck2_.push_back(c30);
    deck2_.push_back(c31);
}

void GameWindow::initDeck3(){
    std::string c1 = "000074w";
    std::string c2 = "000075w";
    std::string c3 = "300364w";
    std::string c4 = "033533w";
    std::string c5 = "700004b";
    std::string c6 = "730005b";
    std::string c7 = "630034b";
    std::string c8 = "303353b";
    std::string c9 = "070004g";
    std::string c10 = "073005g";
    std::string c11 = "363004g";
    std::string c12 = "530333g";
    std::string c13 = "007004r";
    std::string c14 = "007305r";
    std::string c15 = "036304r";
    std::string c16 = "353033r";
    std::string c17 = "000704q";
    std::string c18 = "000735q";
    std::string c19 = "003634q";
    std::string c20 = "335303q";
    deck3_.push_back(c1);
    deck3_.push_back(c2);
    deck3_.push_back(c3);
    deck3_.push_back(c4);
    deck3_.push_back(c5);
    deck3_.push_back(c6);
    deck3_.push_back(c7);
    deck3_.push_back(c8);
    deck3_.push_back(c9);
    deck3_.push_back(c10);
    deck3_.push_back(c11);
    deck3_.push_back(c12);
    deck3_.push_back(c13);
    deck3_.push_back(c14);
    deck3_.push_back(c15);
    deck3_.push_back(c16);
    deck3_.push_back(c17);
    deck3_.push_back(c18);
    deck3_.push_back(c19);
    deck3_.push_back(c20);
}


void GameWindow::initNobels(){

    //nobel *n = new nobel(0,0,1,1,1,1,1,1);
    //scene3->addItem(n);
    //connect(n, &nobel::nobelClicked, this, &GameWindow::nobelClickedSlot);

    std::string n  =  "33030";
    std::string n2 =  "03330";
    std::string n3 =  "30303";
    std::string n4 =  "30033";
    std::string n5 =  "33300";
    std::string n6 =  "40400";
    std::string n7 =  "40004";
    std::string n8 =  "40040";
    std::string n9 =  "04040";
    std::string n10 = "04400";
    nobels_.push_back(n);
    nobels_.push_back(n2);
    nobels_.push_back(n3);
    nobels_.push_back(n4);
    nobels_.push_back(n5);
    nobels_.push_back(n6);
    nobels_.push_back(n7);
    nobels_.push_back(n8);
    nobels_.push_back(n9);
    nobels_.push_back(n10);


}


/**
 * @brief GameWindow::drawNobels
 * @param x
 * @param y
 * @param info
 * @return
 *
 * just a noble factory
 * didnt spell noble right
 */
nobel* GameWindow::drawNobels(int x, int y, std::string info){
    //nobel(int x, int y,int cnD, int cnE, int cnR, int cnS, int cnQ, int nvp);
    int D = (info[0]) - ('0');
    int E = (info[1]) - ('0');
    int R = (info[2]) - ('0');
    int S = (info[3]) - ('0');
    int Q = (info[4]) - ('0');


    return new nobel(x, y, D, E, R, S, Q, 5);

}


/**
 * @brief GameWindow::setNobels
 *
 * draw the nobles in their scene
 * calls noble constructor with randome inputs from the possible list of nobles
 */
void GameWindow::setNobels(){

    int itr = numPl_ + 1;
    unsigned int size = nobels_.size() + 1;
    srand(time(0));
    for(int i = 0; i < itr; i++){
        unsigned int index = rand() % (nobels_.size() + 1);
        nobel *n = drawNobels(i*157, 0, nobels_[index]);
        connect(n , &nobel::nobelClicked, this, &GameWindow::nobelClickedSlot);
        scene3->addItem(n);
        nobels_.erase(nobels_.begin() + (int)index);
    }

}


/**
 * @brief GameWindow::AIhandler
 * @param plr
 *
 * controll the CPU
 * can only buy 3 gems or pass
 */
void GameWindow::AIhandler(Player *plr){
    bool take = false;

    int D = plr->dim;
    int E = plr->emd;
    int S = plr->sap;
    int Q = plr->qrt;
    int R = plr->rby;

    //tries to get 3 of each type before it starts to buy cards
    //after buying 1 card it wants 2 of each type from then on
    //it then focuses on buying cards

    if (gnumD_ >= 3 && D < 3){
        gnumD_ -= 3;
        plr->dim += 3;
        plr->cD_ += 3;
        take = true;
    }
    else if (gnumE_ >= 3 && E < 3){
        gnumE_ -= 3;
        plr->emd += 3;
        plr->cE_ += 3;
        take = true;
    }
    else if (gnumS_ >= 3 && S < 3){
        gnumS_ -= 3;
        plr->sap += 3;
        plr->cE_ += 3;
        take = true;
    }
    else if (gnumQ_ >= 3 && Q < 3){
        gnumQ_ -= 3;
        plr->qrt += 3;
        plr->cQ_ += 3;
        take = true;
    }
    else if (gnumR_ >= 3 && R < 3){
        gnumR_ -= 3;
        plr->rby += 3;
        plr->cR_ += 3;
        take = 3;
    }

    CurrAcc_ = CurrentAction::EndTurn;
    UpdateGemLbl();
    PlayerDir(CurrAcc_,plr);

    //message player what the cpu did
    if (take){
        QMessageBox::about(this,"GM Says", "CPU has taken 3 gems. Hit End Turn to continue to next player");
    }
    else{
        QMessageBox::about(this, "GM Says", "CPU has passed the turn. Hit End Turn to continue to next player");
    }
}
