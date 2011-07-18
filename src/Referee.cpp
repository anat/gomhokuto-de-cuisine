/* 
 * File:   Referee.cpp
 * Author: fancel
 *
 * Created on May 5, 2011, 1:14 PM
 */

#include <iostream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>

#include "Referee.hpp"
#include "Game.hpp"

Referee::Referee(Board& board)
: _winLineList(), _board(board), _threeChecker(_board), _score(), _winner(0) {
    _score[0] = _score[1] = 0;
}

Referee::Referee(const Referee& orig)
: _winLineList(orig._winLineList), _board(orig._board), _threeChecker(_board), _score(orig._score), _winner(orig._winner) {
}

Referee::Referee(const Referee& orig, Board& board)
: _winLineList(orig._winLineList), _board(board), _threeChecker(_board), _score(orig._score), _winner(orig._winner) {
}

Referee::~Referee() {
}

void Referee::setScore(unsigned int player, unsigned int value) {
    _score[player & 1] = value;
}

unsigned int Referee::getScore(unsigned int player) const {
    return _score[player & 1];
}

/**
 * deplace x et y dans la direction choisie
 */
bool Referee::goTo(unsigned int& x, unsigned int& y, RefereeManager::Vector dir) const {
    return RefereeManager::Instance().goTo(_board.getSize(), x, y, dir);
}

unsigned int Referee::getDirAlign(const Square& square, RefereeManager::Vector dir) const {
    return RefereeManager::Instance().getDirAlign(square, dir);
}

void Referee::setDirAlign(Square& square, RefereeManager::Vector dir, unsigned int lineSize) {
    RefereeManager::Instance().setDirAlign(square, dir, lineSize);
}

unsigned int Referee::getDirEnd(const Square& square, RefereeManager::Vector dir) const {
    return Singleton<RefereeManager>::Instance().getDirEnd(square, dir);
}

void Referee::setDirEnd(Square& square, RefereeManager::Vector dir, unsigned int endValue) {
    Singleton<RefereeManager>::Instance().setDirEnd(square, dir, endValue);
}

/*
 * Teste si la case fait partie d'au moins un alignement superieur ou egale a 'size'
 */
bool Referee::ispartOfAlign(const Square& value, unsigned int size) {
    //value.dumpData();
    unsigned int diagl = value.getDiagl();
    unsigned int diagr = value.getDiagr();
    unsigned int horz = value.getHorz();
    unsigned int vert = value.getVert();

    if (diagl >= size || diagr >= size || horz >= size || vert >= size) {
        return true;
    }
    return false;
}

/*
 * Teste si la case fait partie d'au moins un alignement de 'size'
 */
bool Referee::ispartOfExactAlign(const Square& value, int size) {
    return (
            GET_DIAGL(value.getRawData()) == size ||
            GET_DIAGR(value.getRawData()) == size ||
            GET_HORZ(value.getRawData()) == size ||
            GET_VERT(value.getRawData()) == size
            );
}

void Referee::setRaw(Square& value, unsigned int val) {
    value.setRawData(val);
}

void Referee::setTakable(Square& square, bool value) {
    square.setIsTackable(value);
}

/**
 * get de l'atribut qui contient le gagnant
 */
unsigned int Referee::checkWin() const {
    return _winner;
}

/**
 * reset le gagnant
 */
void Referee::reset() {
    _winner = 0;
}

/**
 * Tente de placer une pierre
 */
int Referee::tryPlaceRock(unsigned int x, unsigned int y, unsigned int player) {
    int value = -1;

    if (testPosition(x, y, player)) {
        std::cout << "test" << std::endl;
        _board(x, y).setPlayer(player);
        std::cout << "set" << std::endl;
        fpropagation(x, y, player);
        std::cout << "propag" << std::endl;
        value = checkPrize(x, y, player);
        std::cout << "check" << std::endl;
        if (value) {
            setScore(player, getScore(player) + value * 2);
            std::cout << "score" << std::endl;
        }
        checkIsTakable(x, y, player);
        std::cout << "check" << std::endl;
        checkWin(x, y, player);
        std::cout << "win" << std::endl;
    }
    return value;
}

/**
 * Determine si la position est valide pour une nouvelle pierre
 */
bool Referee::testPosition(unsigned int x, unsigned int y, unsigned int player) {
    bool value = false;

    if (checkPosition(x, y) && GET_PLAYER(_board(x, y).getRawData()) == 0) { //rajouter les tests de pattern ici

        value = true;
        if (Singleton<RefereeManager>::Instance().doubleThree())
            value = checkDoubleThree(x, y, player);
    }
    return value;
}

/**
 * cherche dans toute les directions si il a des pierre a prendre
 */
unsigned int Referee::checkPrize(unsigned int x, unsigned int y, unsigned int player) {
    unsigned int result = 0;
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

    for (unsigned int i = 1; i < dir.size(); i++) {
        if (checkPrize(x, y, dir[i], player)) {
            cleanRock(x, y, dir[i], player);
            result++;
        }
    }

    return result;
}

void Referee::checkPrizeRun(CheckPrizeInfo& info) {
    if (checkPrize(info.x, info.y, info.dir, info.player)) {
        cleanRock(info.x, info.y, info.dir, info.player);
        info.result++;
    }
}

/**
 * cherche si il y a une prise dans une direction
 */
bool Referee::checkPrize(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const {
    std::cout << "check Prize" << std::endl;
    if (checkCanTake(x, y, dir, player)) {
        goTo(x, y, dir);
        _board(x, y).setIsTackable(true);

        goTo(x, y, dir);
        _board(x, y).setIsTackable(true);

        if (goTo(x, y, dir) && _board(x, y).getPlayer() == player)
            return true;
    }
    return false;
}

/**
 * check si les pions dans la direction sont prenable par le joueurs player
 */

bool Referee::checkCanTake(unsigned x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const {
    std::cout << "checkCanTake" << std::endl;
#ifdef DEBUG
    if (goTo(x, y, dir)) {
        unsigned int playertmp = GET_PLAYER(_board(x, y).getRawData());
        unsigned int align = getDirAlign(_board(x, y), dir);
        return (playertmp == opponant(player) && align == 2 && goTo(x, y, dir) && goTo(x, y, dir));
    }
    return false;
#else
    return (goTo(x, y, dir) &&
            (_board(x, y).getPlayer() == Referee::opponant(player)) &&
            (getDirAlign(_board(x, y), dir) == 2) && goTo(x, y, dir) && goTo(x, y, dir));
#endif
}

/**
 * clean les pierre trouver comme prise
 */
void Referee::cleanRock(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) {
    std::cout << "cleanRock" << std::endl;
    unsigned int xtmp, ytmp;

    goTo(x, y, dir);
    //std::cout << "## x " << x << " ## y " << y << std::endl;
    setRaw(_board(x, y), 0);
    xtmp = x;
    ytmp = y;

    goTo(x, y, dir);
    //std::cout << "## x " << x << " ## y " << y << std::endl;
    setRaw(_board(x, y), 0);

    fpropagation_inverse(xtmp, ytmp, Referee::opponant(player));
    fpropagation_inverse(x, y, Referee::opponant(player));
}

void Referee::checkIsTakable(unsigned int x, unsigned int y, unsigned int player) {
    setTakable(_board(x, y), false);
    if (ispartOfExactAlign(_board(x, y), 2)) {

        const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

        for (unsigned int i = 1; i < dir.size(); ++i) {
            if (checkIsTakable(x, y, dir[i], player)) {
                unsigned int xtmp = x;
                unsigned int ytmp = y;

                setTakable(_board(x, y), true);
                goTo(xtmp, ytmp, dir[i]);
                setTakable(_board(xtmp, ytmp), true);
            }
        }
    }
}

bool Referee::checkIsTakable(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) const {
    unsigned int xinv = x;
    unsigned int yinv = y;

    return (getDirAlign(_board(x, y), dir) == 2 && goTo(xinv, yinv, RefereeManager::Instance().invert(dir)) && goTo(x, y, dir) && goTo(x, y, dir) &&
            ((GET_PLAYER(_board(xinv, yinv).getRawData()) == Referee::opponant(player) || GET_PLAYER(_board(x, y).getRawData()) == Referee::opponant(player)) && !(GET_PLAYER(_board(xinv, yinv).getRawData()) == Referee::opponant(player) && GET_PLAYER(_board(x, y).getRawData()) == Referee::opponant(player))));
}

/**
 * Determine si le coup est gagnant
 */
void Referee::checkWin(unsigned int x, unsigned int y, unsigned int player) {
    if (getScore(player) >= 10)
        _winner = player;
    else if (ispartOfAlign(_board(x, y), 5)) {
        _winLineList.push_back(Coord(x, y));
        checkWinList();
        //if (_winner)
        //  _board.DumpBoard();
    }
}

void Referee::checkWinList() {
    WinList::iterator it = _winLineList.begin();
    WinList::iterator ite = _winLineList.end();

    while (!_winner && it != ite && _board(it->x, it->y).getPlayer() && ispartOfAlign(_board(it->x, it->y), 5)) {
        if (RefereeManager::Instance().fivePrize()) {
            if (checkFivePrize(it->x, it->y))
                _winner = _board(it->x, it->y).getPlayer();
        } else {
            _winner = _board(it->x, it->y).getPlayer();
        }
        ++it;
    }
    if (!_winner && it != ite) {
        _winLineList.erase(it);
        checkWinList();
    }
    if (_winner) {
        _winLineList.clear();
    }
}

/**
 * Fonction de test de la regle speciale des 5 pions lors d'une tentative de victoire
 */
bool Referee::checkFivePrize(unsigned int x, unsigned int y) {
    unsigned int player = _board(x, y).getPlayer();

    if (player) {
        if (_board(x, y).getDiagl() > 4) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::UP_LEFT, player);
            size += checkFivePrize(x, y, RefereeManager::DOWN_RIGHT, player);
            size++;
            if (size > 4)
                return true;
        }

        if (_board(x, y).getDiagr() > 4) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::UP_RIGHT, player);
            size += checkFivePrize(x, y, RefereeManager::DOWN_LEFT, player);
            size++;
            if (size > 4)
                return true;
        }

        if (_board(x, y).getHorz() > 4) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::RIGHT, player);
            size += checkFivePrize(x, y, RefereeManager::LEFT, player);
            size++;
            if (size > 4)
                return true;
        }

        if (_board(x, y).getVert() > 4) {
            unsigned int size = checkFivePrize(x, y, RefereeManager::UP, player);
            size += checkFivePrize(x, y, RefereeManager::DOWN, player);
            size++;
            if (size > 4)
                return true;
        }
    }

    return false;
}

unsigned int Referee::checkFivePrize(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player) {
    int cleanRock = 0;

    while (goTo(x, y, dir) && (_board(x, y).getPlayer() == player) && (_board(x, y).getIsTakable() == false)) {
        cleanRock++;
    }
    return cleanRock;
}

/**
 * Get/Set pour les regles speciales
 */
bool Referee::doubleThree() const {
    return RefereeManager::Instance().doubleThree();
}

bool Referee::doubleThree(bool value) {
    RefereeManager::Instance().setDoubleThree(value);
    return RefereeManager::Instance().doubleThree();
}

bool Referee::fivePrize() const {
    return RefereeManager::Instance().fivePrize();
}

bool Referee::fivePrize(bool value) {
    RefereeManager::Instance().setFivePrize(value);
    return RefereeManager::Instance().fivePrize();
}

/*
 * Fonction de test de la regle speciale des double 3 pions align
 */
bool Referee::checkDoubleThree(unsigned int x, unsigned int y, unsigned int player) {
    return _threeChecker.CheckDoubleThree(x, y, player);
}

/* Try to propagate in EVERY directions */

void Referee::fpropagation(unsigned int x, unsigned int y, const unsigned int player) {
    boost::thread_group threadGroup;

    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::UP, player)
            );
    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::LEFT, player)
            );
    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::UP_RIGHT, player)
            );
    threadGroup.create_thread(
            boost::bind(&Referee::fpropagation_dir, this, x, y, RefereeManager::UP_LEFT, player)
            );
    
    threadGroup.join_all();
    //fpropagation(x, y, RefereeManager::UP, player);
    //fpropagation(x, y, RefereeManager::LEFT, player);
    //fpropagation(x, y, RefereeManager::UP_RIGHT, player);
    //fpropagation(x, y, RefereeManager::UP_LEFT, player);
}

void Referee::fpropagation_dir(unsigned int x, unsigned int y, RefereeManager::Vector dir, const unsigned int player) {
    PropagationInfo info;

    info = flineSize(x, y, dir, player) + flineSize(x, y, RefereeManager::Instance().invert(dir), player);
    info.lineSize += 1;
    setDirAlign(_board(x, y), dir, info.lineSize);
    setDirEnd(_board(x, y), dir, info.endBlock);

    fsetline(x, y, dir, player, info);
    fsetline(x, y, RefereeManager::Instance().invert(dir), player, info);
}

void Referee::fpropagation_inverse(unsigned int x, unsigned int y, const unsigned int player) {
    std::cout << "propagation inverse" << std::endl;
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

    for (unsigned int i = 1; i < dir.size(); i++) {
        fpropag_inverse_to(x, y, dir[i], player);
    }
}

void Referee::fpropag_inverse_to(unsigned int x, unsigned int y, Vector dir, const unsigned int player) {
    if (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        fpropagation(x, y, player);
        checkIsTakable(x, y, player);
    }
}

Referee::PropagationInfo Referee::flineSize(unsigned int x, unsigned int y, Vector dir, unsigned int player) {
    PropagationInfo info;

    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player)
        info.lineSize++;
    if (GET_PLAYER(_board(x, y).getRawData()) != Referee::opponant(player)) {
        info.endBlock++;
    }

    if (info.lineSize == 0 && GET_PLAYER(_board(x, y).getRawData()) == Referee::opponant(player)) {
        unsigned int opponant_end = getDirEnd(_board(x, y), dir);
        opponant_end--;
        setDirEnd(_board(x, y), dir, opponant_end);
        while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == Referee::opponant(player))
            setDirEnd(_board(x, y), dir, opponant_end);
    }

    return info;
}

void Referee::fsetline(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player, const PropagationInfo& value) {
    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        setDirAlign(_board(x, y), dir, value.lineSize);
        setDirEnd(_board(x, y), dir, value.endBlock);
        if (!ispartOfExactAlign(_board(x, y), 2))
            setTakable(_board(x, y), false);
    }
}

void Referee::resetTakable(unsigned int x, unsigned int y, RefereeManager::Vector dir, unsigned int player, bool takable) {
    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) == player) {
        setTakable(_board(x, y), takable);
    }
}

void Referee::dumpSquare(unsigned int x, unsigned int y) const {
    std::cout << "###########" << std::endl;
    std::cout << "x = " << x << " y= " << y << std::endl;
    std::cout << "player " << GET_PLAYER(_board(x, y).getRawData()) << std::endl;
    std::cout << "takable ";
    if (GET_TAKABLE(_board(x, y).getRawData()))
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
    std::cout << "align horz " << _board(x, y).getHorz() << std::endl;
    std::cout << "align vert " << _board(x, y).getVert() << std::endl;
    std::cout << "align DiagL " << _board(x, y).getDiagl() << std::endl;
    std::cout << "align DiagR " << _board(x, y).getDiagr() << std::endl;
    std::cout << "###########" << std::endl;
}

void Referee::dumpDirection(unsigned int x, unsigned int y, RefereeManager::Vector dir) const {
    while (goTo(x, y, dir) && GET_PLAYER(_board(x, y).getRawData()) != 0)
        dumpSquare(x, y);
}

void Referee::dumpPropagation(unsigned int x, unsigned int y) const {
    const RefereeManager::VectorArray& dir = RefereeManager::Instance().getVectorArray();

    dumpSquare(x, y);
    for (unsigned int i = 1; i < dir.size(); i++) {
        dumpDirection(x, y, dir[i]);
    }
}
