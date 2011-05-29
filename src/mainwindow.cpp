#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _game = new Game();
    _scene = NULL;
    _sizeboard = 19;
    _border = 25;

    QObject::connect(_ui->actionNew, SIGNAL(triggered()), this, SLOT(print_status()));
    QObject::connect(_ui->actionParameters, SIGNAL(triggered()), this, SLOT(print_circle()));
    QObject::connect(this, SIGNAL(ReadyToDraw()), this, SLOT(DrawAll()));
    QObject::connect(this, SIGNAL(SignalPosMouse(int,int)), this, SLOT(trytopose(int,int)));
}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _game;
    delete _scene;
}

void MainWindow::InfoDraw()
{

    float size = (float) _sizeboard;

    _height = (float)_ui->WGameBoard->height();
    _width = (float)_ui->WGameBoard->width();
    _heightWB = _height - 2 * _border;
    _widthWB = _width - 2 * _border;
    _refh = _heightWB / (size - 1);
    _refw = _widthWB / (size - 1);
    std::cout << "_height= " << _height << std::endl <<
                 "_width= " << _width << std::endl <<
                 "_border= " << _border << std::endl <<
                 "_refh= " << _refh << std::endl <<
                 "_refw= " << _refw << std::endl <<
                 "_heightWB= " << _heightWB << std::endl <<
                 "_widthWB= " << _widthWB << std::endl;

}

void MainWindow::DrawScene()
{
    if (_scene != NULL)
        delete _scene;
    _scene = new QGraphicsScene(0, 0,
                                _width,
                                _height);
    _ui->GameBoard->setScene(_scene);
}

void MainWindow::DrawShelf(QColor &color)
{ 
    QImage *image = new QImage(":/Background/parquet.jpg");
    QBrush *brush = new QBrush(*image);
    _ui->GameBoard->scene()->setBackgroundBrush(*brush);
    QPen pen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    for (int i = 0; i < _sizeboard; i++)
    {
        QLine v_line(_border + i * _refw, _border,
                     _border + i * _refw, _heightWB + _border);
        QLine h_line(_border, _border + i * _refh,
                     _widthWB + _border, _border + i * _refh);
        _ui->GameBoard->scene()->addLine(h_line, pen);
        _ui->GameBoard->scene()->addLine(v_line, pen);
    }
    DrawMark(color, _border + 3 * _refw, _border + 3 * _refh);
    DrawMark(color, _border + 3 * _refw, _border + 9 * _refh);
    DrawMark(color, _border + 3 * _refw, _border + 15 * _refh);
    DrawMark(color, _border + 9 * _refw, _border + 3 * _refh);
    DrawMark(color, _border + 9 * _refw, _border + 9 * _refh);
    DrawMark(color, _border + 9 * _refw, _border + 15 * _refh);
    DrawMark(color, _border + 15 * _refw, _border + 3 * _refh);
    DrawMark(color, _border + 15 * _refw, _border + 9 * _refh);
    DrawMark(color, _border + 15 * _refw, _border + 15 * _refh);
}

void MainWindow::DrawMark(QColor &color, int x, int y)
{

    QPen pen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QAbstractGraphicsShapeItem* i = _ui->GameBoard->scene()->addEllipse(QRectF(0,0,8,8), pen);
    i->setBrush(color);
    i->setPos(x - 4, y - 4);
}

void MainWindow::DrawPiece(int x, int y)
{
    std::cout << "DrawPiece enter" << std::endl;
    QAbstractGraphicsShapeItem* i = _ui->GameBoard->scene()->addEllipse(QRectF(0, 0, 30, 30));
    //i->setFlag(QGraphicsItem::ItemIsMovable);
    i->setPen(Qt::NoPen);
    i->setBrush( QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8) );
    i->setPos(x - 15, y - 15);
}

void MainWindow::DrawBoard()
{
    for (int x = 0; x < this->_sizeboard; x++)
        for (int y = 0; y < this->_sizeboard; y++)
        {
            switch (this->_game->getGameBoard().getCase(x, y).getData().player)
            {
            case PLAYER1:
                this->DrawPiece(x, y);
                break;
            case PLAYER2:
                this->DrawPiece(x, y);
                break;
            default:
                break;
            }
        }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    event = event;
    std::cout << "signal emit: SignalResize()" << std::endl;
    this->InfoDraw();
    update();
    this->DrawScene();
    emit ReadyToDraw();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    int x, y, nx = -1, ny = -1;
    for (x = 0; x < _sizeboard; x++)
    {
        if ((event->pos().x() > (float)x * _refw + _border - _refw / 2) &&
            (event->pos().x() < (float)x * _refw + _border + _refw / 2))
        {
            nx = x;
            break;
        }
    }
    for (y = 0; y < _sizeboard; y++)
    {
        if ((event->pos().y() > (float)y * _refh + _border - _refh / 2) &&
            (event->pos().y() < (float)y * _refh + _border + _refh / 2))
        {
            ny = y;
            break;
        }
    }
    std::cout << "_height= " << _height << std::endl <<
                 "_width= " << _width << std::endl <<
                 "_border= " << _border << std::endl <<
                 "_refh= " << _refh << std::endl <<
                 "_refw= " << _refw << std::endl <<
                 "_heightWB= " << _heightWB << std::endl <<
                 "_widthWB= " << _widthWB << std::endl <<
                 "x = " << event->pos().x() << std::endl <<
                 "y = " << event->pos().y() << std::endl <<
                 "my new x= " << nx << std::endl <<
                 "my new y= " << ny << std::endl;
    if (ny != -1 && nx != -1)
        emit SignalPosMouse(nx, ny);
}

void MainWindow::print_status()
{
    _ui->statusBar->showMessage("ready to go");
}

void MainWindow::print_circle()
{
}

void MainWindow::DrawAll()
{
    QColor color(Qt::black);

    _ui->GameBoard->scene()->clear();
    this->DrawShelf(color);
    this->DrawBoard();
}

void MainWindow::trytopose(int x, int y)
{
    // inserer dans le tableau, une piece a la position x,y
    emit ReadyToDraw();
}

