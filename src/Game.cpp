/* 
 * File:   Game.cpp
 * Author: cedric.creusot
 * 
 * Created on May 7, 2011, 10:44 AM
 */

#include <iostream>
#include "Game.hpp"
#include "HPlayer.hpp"
#include "PlayerAi.hpp"
#include "BasicHeuristic.hpp"
#include "BasicSearchCase.hpp"

Game::Game(bool vs_computer)
: _players(2), _gameboard(), _referee(_gameboard), _playerTurn(PLAYER1), _vs_computer(vs_computer) {
    if (!vs_computer) {
        _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
        _players[PLAYER2 - 1] = new HPlayer(PLAYER2);
    } else {
        _players[PLAYER1 - 1] = new HPlayer(PLAYER1);
        _players[PLAYER2 - 1] = new PlayerAi< BasicHeuristic, BasicSearchCase >(PLAYER2);
    }
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

bool Game::doGameGui(int x, int y) {
    bool mWinner = false;
    bool doActionIsOk = getCurrentPlayer()->doAction(_gameboard, _referee, x, y);
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
