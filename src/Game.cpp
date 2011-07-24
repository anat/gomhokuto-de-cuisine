/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include <iostream>
#include <QTcpSocket>
#include <QTcpServer>
#include "Game.hpp"
#include "HPlayer.hpp"
#include "PlayerAi.hpp"
#include "BasicHeuristic.hpp"
#include "BasicSearchCase.hpp"
#include "remoteplayer.hpp"
#include "mainwindow.hpp"
#include <QTextCursor>

Game::Game(bool vs_computer, int ServerOrClient, QString * ip, QWidget * parent) :
        _players(2),
        _gameboard(),
        _referee(_gameboard),
        _playerTurn(PLAYER1),
        _vs_computer(vs_computer),
        _serverOrClient(ServerOrClient),
        _mWindow(parent)
{
    if (!vs_computer && ServerOrClient == 0) {
        _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
        _players[PLAYER2 - 1] = new HPlayer(PLAYER2);
    } else if (ServerOrClient == 0) {
        _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
        _players[PLAYER2 - 1] = new PlayerAi< BasicHeuristic, BasicSearchCase >(PLAYER2);
    } else if (ServerOrClient == 1)
    {
        if (_socketServer.listen(QHostAddress::Any, 1338))
        {
            bool hasPlayer = false;
            while (!hasPlayer)
            {
                while (!_socketServer.hasPendingConnections())
                {
                    usleep(10);
                    QCoreApplication::processEvents();
                }
                this->_currentClient = _socketServer.nextPendingConnection();
                while (!this->_currentClient->waitForReadyRead(1))
                    QCoreApplication::processEvents();

                QByteArray a = _currentClient->read(1);
                if (a.count() == 1 && a[0] == 's')
                    _currentClient->close();
                else if (a.count() == 1 && a[0] == 'c')
                {
                    QObject::connect(this->_currentClient, SIGNAL(readyRead()), this, SLOT(dataReceived()));
                    static_cast<MainWindow*>(this->_mWindow)->print_status("Player on " + _currentClient->peerAddress().toString() + ", its your turn !");
                    hasPlayer = true;
                }
                else
                    _currentClient->close();
            }
            _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
            _players[PLAYER2 - 1] = new RemotePlayer(PLAYER2);
        }
        else
            static_cast<MainWindow*>(this->_mWindow)->print_status("Failed to create a game, open your 1338 port !");
    }
    else if (ServerOrClient == 2 && ip)
    {
        static_cast<MainWindow*>(this->_mWindow)->print_status("Connecting to " + *ip);
        _socketClient.connectToHost(QHostAddress(*ip), 1338);
        if (_socketClient.waitForConnected(5000))
        {
            _socketClient.write("c", 1);
            static_cast<MainWindow*>(this->_mWindow)->print_status(QString("Connected to ") + *ip + QString(", it's not your turn !"));
            QObject::connect(&this->_socketClient, SIGNAL(readyRead()), this, SLOT(dataReceived()));
        }
        else
            static_cast<MainWindow*>(this->_mWindow)->print_status("Connection failed !");
        _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
        _players[PLAYER2 - 1] = new RemotePlayer(PLAYER2);
        _playerTurn = (_playerTurn == PLAYER1) ? (PLAYER2) : (PLAYER1);
    }
    if (ServerOrClient)
    {
        QObject::connect(static_cast<MainWindow*>(this->_mWindow)->getChatLine(), SIGNAL(returnPressed()), this, SLOT(sendMessage()));
    }
}

void Game::sendMessage()
{
    if (_serverOrClient == 1)
        _currentClient->write(QString("c" + static_cast<MainWindow*>(this->_mWindow)->getChatLine()->text()).toStdString().c_str()
                                ,QString("c" + static_cast<MainWindow*>(this->_mWindow)->getChatLine()->text()).length());

    else if (_serverOrClient == 2)
        _socketClient.write(QString("c" + static_cast<MainWindow*>(this->_mWindow)->getChatLine()->text()).toStdString().c_str()
                                ,QString("c" + static_cast<MainWindow*>(this->_mWindow)->getChatLine()->text()).length());

    static_cast<MainWindow*>(this->_mWindow)->getChatContent()->append("\nMe: " +
                                                                       static_cast<MainWindow*>(this->_mWindow)->getChatLine()->text());
    static_cast<MainWindow*>(this->_mWindow)->getChatLine()->setText("");
    static_cast<MainWindow*>(this->_mWindow)->getChatContent()->textCursor().setPosition(static_cast<MainWindow*>(this->_mWindow)->getChatContent()->toPlainText().length());
}

void Game::dataReceived()
{
    bool mWinner = false;
    QByteArray r;
    if (_serverOrClient == 1)
        r = _currentClient->readAll();
    else
        r = _socketClient.readAll();
    if (r.constData()[0] == 'g')
    {
        int coord[2];
        memcpy(coord, r.constData() + 1, sizeof(int) * 2);
        bool doActionIsOk = getCurrentPlayer()->doAction(_gameboard, _referee, coord[0], coord[1]);
        mWinner = checkWin();

        emit clear();
        if (mWinner) {
            _gameboard.DumpBoard();
            emit winner(_playerTurn);
        }
        if (doActionIsOk)
        {
            _playerTurn = (_playerTurn == PLAYER1) ? (PLAYER2) : (PLAYER1);
            static_cast<MainWindow*>(_mWindow)->DrawAll();
        }
    }
    if (r.constData()[0] == 'c')
    {
        if (_serverOrClient == 1)
            static_cast<MainWindow*>(this->_mWindow)->getChatContent()->append("\n" + _currentClient->peerAddress().toString() + ": " + QString(r.constData() + 1));
        if (_serverOrClient == 2)
            static_cast<MainWindow*>(this->_mWindow)->getChatContent()->append("\n" + _socketClient.peerAddress().toString() + ": " + QString(r.constData() + 1));
        static_cast<MainWindow*>(this->_mWindow)->getChatContent()->textCursor().setPosition(static_cast<MainWindow*>(this->_mWindow)->getChatContent()->toPlainText().length());

    }
}

QTcpSocket* Game::getCurrentClient()
{
    if (_serverOrClient == 1)
        return _currentClient;
    else
        return &_socketClient;
}

Game::~Game() {
}

unsigned int Game::getPlayerTurn() {
    return (_playerTurn);
}

APlayer * Game::getCurrentPlayer() {
    int i = (int) _playerTurn;
    return (_players[i - 1]);
}

std::vector<APlayer*> const & Game::getPlayers() const {
    return (_players);
}

void Game::connectionLost()
{
    if (_serverOrClient == 1)
        QObject::disconnect(&this->_socketClient, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    if (_serverOrClient == 2)
        QObject::disconnect(this->_currentClient, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    QObject::disconnect(static_cast<MainWindow*>(this->_mWindow)->getChatLine(), SIGNAL(returnPressed()), this, SLOT(sendMessage()));
    static_cast<MainWindow*>(this->_mWindow)->print_status("Connection lost !");
}

bool Game::doGameGui(int x, int y) {
    bool mWinner = false;
    int coord[2];
    coord[0] = x;
    coord[1] = y;
    char buffer[(sizeof(int) * 2) + 1];
    memcpy(buffer, "g", 1);
    memcpy(buffer + 1, &x, sizeof(int));
    memcpy(buffer + 1 + sizeof(int), &y, sizeof(int));
    bool doActionIsOk = getCurrentPlayer()->doAction(_gameboard, _referee, x, y);
    if (doActionIsOk)
    {
        if (_serverOrClient == 1)
            _currentClient->write(buffer, (sizeof(int) * 2) + 1);
        if (_serverOrClient == 2)
            _socketClient.write(buffer, (sizeof(int) * 2) + 1);
    }
    if (!(mWinner = checkWin()) && doActionIsOk) {
        if (_vs_computer)
        {
            _playerTurn = (_playerTurn == PLAYER1) ? (PLAYER2) : (PLAYER1);
            doActionIsOk = getCurrentPlayer()->doAction(_gameboard, _referee);
            mWinner = checkWin();
        }
    }
    emit clear();
    if (mWinner) {
        _gameboard.DumpBoard();
        emit winner(_playerTurn);
    }
    if (doActionIsOk)
        _playerTurn = (_playerTurn == PLAYER1) ? (PLAYER2) : (PLAYER1);
    return (mWinner);
}

bool Game::checkWin() {
    if (_referee.checkWin() != NOPLAYER)
        return true;
    return false;
}

Board & Game::getGameBoard() {
    return (_gameboard);
}

bool Game::getFivePrize() {
    return (_referee.fivePrize());
}

bool Game::getDoubleThree() {
    return (_referee.doubleThree());
}

void Game::setFivePrize(bool value) {
    _referee.fivePrize(value);
}

void Game::setDoubleThree(bool value) {
    _referee.doubleThree(value);
}

const Referee& Game::getReferee() const {
    return _referee;
}
