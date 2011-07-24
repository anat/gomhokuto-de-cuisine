#include "newgame.hpp"
#include "ui_newgame.h"
#include "mainwindow.hpp"
#include <QNetworkAddressEntry>
#include <QListWidgetItem>
NewGame::NewGame(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NewGame),
        _isNetworkGame(false),
        _createOrJoin(0)
{
    ui->setupUi(this);
    _game = NULL;
    _winner = -1;
    ui->ComputOrHuman->setChecked(true);
    ui->VsHuman->setChecked(true);
    ui->WhiteColor->setChecked(true);

    QObject::connect(ui->ComputOrHuman, SIGNAL(clicked(bool)), this, SLOT(CompVSComp(bool)));
    QObject::connect(ui->cbNetwork, SIGNAL(clicked(bool)), this, SLOT(NetworkGame(bool)));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(CreateNewGame()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(CancelNewGame()));
    QObject::connect(ui->cbNetwork, SIGNAL(clicked(bool)),this, SLOT(isNetwork(bool)));
    QObject::connect(ui->btnCreate, SIGNAL(clicked()), this, SLOT(Create()));
    QObject::connect(ui->btnJoin, SIGNAL(clicked()), this, SLOT(Join()));
    QObject::connect(ui->listRefresh, SIGNAL(clicked()), this, SLOT(refreshGames()));
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
    ui->Color->setEnabled(val);
    ui->Versus->setEnabled(val);
    ui->buttonBox->setEnabled(val);
    ui->cbNetwork->setEnabled(val);
}

void NewGame::CreateNewGame()
{
    static_cast<MainWindow*>(this->parent())->getChatLine()->setEnabled(false);
    if (_game != NULL)
    {
        delete _game;
        _game = NULL;
        _winner = -1;
    }
    if (_isNetworkGame)
    {
        static_cast<MainWindow*>(this->parent())->getChatLine()->setEnabled(true);
        static_cast<MainWindow*>(this->parent())->print_status("Waiting for player ...");
        if (_createOrJoin == 1)
            _game = new Game(false, _createOrJoin, NULL, static_cast<QWidget*>(this->parent()));
        else
        {
            QString* ip = NULL;
            QListWidgetItem* current = this->ui->listGame->currentItem();
            if (current)
                ip = new QString(current->text());
            else
            {
                bool ok;
                ip = new QString(QInputDialog::getText(this, "Enter IP", "Please enter Host/IP:",QLineEdit::Normal, "", &ok, 0));
                if (!ok)
                    return ;
            }
            _game = new Game(false, _createOrJoin, ip, static_cast<QWidget*>(this->parent()));
        }
    }
    else if (ui->ComputOrHuman->isChecked() == true)
    {
        if (ui->VsHuman->isChecked() == true)
            _game = new Game();
        else
            _game = new Game(true);
    }

    QObject::connect(this->_game, SIGNAL(winner(int)), this, SLOT(TheWinnerIs(int)));
    emit SignalClear();
}

void NewGame::Join()
{
    _createOrJoin = 2;
    CreateNewGame();
    this->hide();
}

void NewGame::Create()
{
    _createOrJoin = 1;
    CreateNewGame();
    this->hide();
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

void NewGame::isNetwork(bool is)
{
    this->ui->buttonBox->setEnabled(!is);
    this->ui->TWNetwork->setEnabled(is);
}

void NewGame::NetworkGame(bool nGame)
{
    _isNetworkGame = nGame;
}

void NewGame::refreshGames()
{
    this->ui->listRefresh->setEnabled(false);
    this->ui->listGame->clear();
    unsigned int ip;
    unsigned int netmask = 0xffffff00;
    foreach (QNetworkInterface it, QNetworkInterface::allInterfaces())
        foreach (QHostAddress addr, it.allAddresses())
            if (addr.toIPv4Address() && 0xff000000 != 0x7f000000)
                ip = addr.toIPv4Address();
    unsigned int networkaddr = ip & netmask;
    for (unsigned int i = 1; i < 256; i++)
    {
        unsigned int currentIp = networkaddr + i;
        QTcpSocket* s = new QTcpSocket();
        s->connectToHost(QHostAddress(currentIp), 1338);
        static_cast<MainWindow*>(this->parent())->print_status("Scanning ...\tCurrent : " + QHostAddress(currentIp).toString());
        if (s->waitForConnected(5))
        {
            this->ui->listGame->addItem(new QListWidgetItem(QHostAddress(currentIp).toString()));
            QCoreApplication::processEvents();
            // tell the slave this is just a search request
            s->write("s", 1);
            s->close();
        }
    }
    static_cast<MainWindow*>(this->parent())->print_status("End of scan");
    this->ui->listRefresh->setEnabled(true);
}
