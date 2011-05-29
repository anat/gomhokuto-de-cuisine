#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _param = new Parameters(this);
    _ui->setupUi(this);
    _game = new Game();
    _scene = NULL;
    _sizeboard = 19;
    _border = 25;

    QObject::connect(_ui->actionParameters, SIGNAL(triggered()), this, SLOT(ShowParameter()));

    QObject::connect(_ui->actionQuitter, SIGNAL(triggered()), _param, SLOT(close()));
    QObject::connect(_ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(this, SIGNAL(ReadyToDraw()), this, SLOT(DrawAll()));
    QObject::connect(this, SIGNAL(SignalPosMouse(int,int)), this, SLOT(trytopose(int,int)));
    QObject::connect(this, SIGNAL(SignalPosMouse(int,int)), this, SLOT(print_status(int,int)));
    QObject::connect(this->_param, SIGNAL(SignalModif()), this, SLOT(DrawAll()));
    QObject::connect(this->_game, SIGNAL(winner(int)), this, SLOT(TheWinnerIs(int)));
    QObject::connect(this->_param, SIGNAL(SignalDoubleThree(int)), this, SLOT(checkDoubleThree(int)));
    QObject::connect(this->_param, SIGNAL(SignalFivePrize(int)), this, SLOT(checkFivePrize(int)));
}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _game;
    delete _scene;
    delete _param;
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


    std::cout << "DoubleThree= " << this->_game->getDoubleThree() << std::endl <<
                 "FivePrize= " << this->_game->getFivePrize() << std::endl;
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
    QImage *image = new QImage(_param->GetBackground());
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

void MainWindow::DrawPiece(QColor &color, int x, int y)
{
    std::cout << "DrawPiece enter" << std::endl;
    QAbstractGraphicsShapeItem* i = _ui->GameBoard->scene()->addEllipse(QRectF(0, 0, 28, 28));
    //i->setFlag(QGraphicsItem::ItemIsMovable);
    i->setPen(Qt::NoPen);
    i->setBrush(color);
    i->setPos(x - 14, y - 14);
}

void MainWindow::DrawPiece(QString *path)
{
    /*if ( butterfly_fn.isEmpty() )
        return;
    if ( !butterflyimg ) {
        butterflyimg = new QImage[4];
        butterflyimg[0].load( butterfly_fn );
        butterflyimg[1] = butterflyimg[0].scaled( int(butterflyimg[0].width()*0.75),
                int(butterflyimg[0].height()*0.75), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        butterflyimg[2] = butterflyimg[0].scaled( int(butterflyimg[0].width()*0.5),
                int(butterflyimg[0].height()*0.5), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        butterflyimg[3] = butterflyimg[0].scaled( int(butterflyimg[0].width()*0.25),
                int(butterflyimg[0].height()*0.25), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    QAbstractGraphicsShapeItem* i = new ImageItem(butterflyimg[qrand()%4]);
    canvas.addItem(i);
    i->setPos(qrand()%int(canvas.width()-butterflyimg->width()),
            qrand()%int(canvas.height()-butterflyimg->height()));
    i->setZValue(qrand()%256+250);
    */
}

void MainWindow::DrawBoard()
{
    for (int x = 0; x < this->_sizeboard; x++)
        for (int y = 0; y < this->_sizeboard; y++)
        {
            switch (this->_game->getGameBoard().getCase(x, y).getData().player)
            {
            case PLAYER1:
{
                QColor color1(Qt::black);
                this->DrawPiece(color1, _border + x * _refw,
                                _border + y * _refh);
                break;
}
            case PLAYER2:
{                QColor color2(Qt::white);
                this->DrawPiece(color2, _border + x * _refw,
                                _border + y * _refh);
                break;
}
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
    emit this->ReadyToDraw();
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

void MainWindow::print_status(QString text)
{
    _ui->statusBar->showMessage(text);
}

void MainWindow::print_status(int x, int y)
{
    QString res;
    res = "Pose piece on (" + QString::number(x) +
            ", " + QString::number(y) + ")" ;
    _ui->statusBar->showMessage(res, 3000);
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
    _game->doGameGui(x, y);
    x= x; y = y;
    emit ReadyToDraw();
}

void MainWindow::ShowParameter()
{
    _param->show();
}

void MainWindow::TheWinnerIs(int player)
{
    _param->show();
}

void MainWindow::checkDoubleThree(int val)
{
    if (val == 0)
        this->_game->setDoubleThree(false);
    else
        this->_game->setDoubleThree(true);
}

void MainWindow::checkFivePrize(int val)
{
    if (val == 0)
        this->_game->setFivePrize(false);
    else
        this->_game->setFivePrize(true);
}
