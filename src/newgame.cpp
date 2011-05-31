#include "newgame.hpp"
#include "ui_newgame.h"

NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
    _game = NULL;
    _winner = -1;

    ui->ComputOrHuman->setChecked(true);
    ui->VsHuman->setChecked(true);
    ui->WhiteColor->setChecked(true);

    QIntValidator* validator = new QIntValidator(1000,99999, ui->PortText);
    ui->PortText->setValidator(validator);

    QObject::connect(ui->ComputOrHuman, SIGNAL(clicked(bool)), this, SLOT(CompVSComp(bool)));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(CreateNewGame()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(CancelNewGame()));

    //   QObject::connect(this->_game, SIGNAL(SignalReste(int,int)), this, SLOT(SetReste(int,int)));
    //   QObject::connect(this->_Game, SIGNAL(SignalTaken(int,int)), this, SLOT(SetTake(int,int)));

}

NewGame::~NewGame()
{
    delete ui;
    delete _game;
}

Game * NewGame::getGame()
{
    return _game;
}

void NewGame::CompVSComp(bool val)
{
    if (val)
    {
        ui->Color->setEnabled(true);
        ui->Versus->setEnabled(true);
        ui->buttonBox->setEnabled(true);
    }
    else
    {
        ui->Color->setEnabled(false);
        ui->Versus->setEnabled(false);
        ui->buttonBox->setEnabled(false);
    }
}

void NewGame::CreateNewGame()
{
    if (_game != NULL)
    {
        delete _game;
        _game = NULL;
        _winner = -1;
    }
    if (ui->ComputOrHuman->isChecked() == true)
    {
        if (ui->VsHuman->isChecked() == true)
            _game = new Game();
        else
            _game = new Game(true);
    }
    QObject::connect(this->_game, SIGNAL(winner(int)), this, SLOT(TheWinnerIs(int)));
    emit SignalClear();
}

void NewGame::CancelNewGame()
{
    if (_winner != -1)
        emit SignalWinner(_winner);
}

void NewGame::TheWinnerIs(int val)
{
    _winner = val;
    emit SignalWinner(_winner);
}

void NewGame::SetTake(int player, int val)
{
    emit SignalTaken(player, val);
}

void NewGame::SetReste(int player, int val)
{
    emit SignalReste(player, val);
}
