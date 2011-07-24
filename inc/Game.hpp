/* 
 * File:   Game.h
 * Author: cedric.creusot
 *
 * Created on May 7, 2011, 10:44 AM
 */

#ifndef GAME_H
#define	GAME_H

#include <QtGui>
#include <vector>
#include "Referee.hpp"
#include "Board.hpp"
#include "APlayer.hpp"
#include <QTcpSocket>
#include <QTcpServer>

#define NOPLAYER 0
#define PLAYER1 1
#define PLAYER2 2
#define NB_MAX_PLAYER 2

class Game : public QObject {
    Q_OBJECT

public:
    Game(bool vs_computer = false, int ServerOrClient = 0, QString * ip = NULL, QWidget * parent = NULL);
    virtual ~Game();

    unsigned int getPlayerTurn();
    APlayer * getCurrentPlayer();
    std::vector<APlayer*> const & getPlayers() const;
    bool doGameGui(int x, int y);
    bool checkWin();
    Board & getGameBoard();
    bool getDoubleThree();
    bool getFivePrize();
    void setDoubleThree(bool value);
    void setFivePrize(bool value);
    const Referee& getReferee() const;
    QTcpSocket* getCurrentClient();
signals:
    void clear();
    void winner(int player);
public slots:
    void dataReceived();
    void connectionLost();
    void sendMessage();
private:
    std::vector<APlayer*> _players;
    Board _gameboard;
    Referee _referee;
    unsigned int _playerTurn;
    bool _vs_computer;
    QTcpSocket      _socketClient;
    QTcpServer      _socketServer;
    QTcpSocket*     _currentClient;
    int             _serverOrClient;
    QWidget*        _mWindow;
};

#endif	/* GAME_H */

