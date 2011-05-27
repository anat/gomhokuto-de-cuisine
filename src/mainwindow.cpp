#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _game = new Game();
    _sizeboard = 19;
    _ui->setupUi(this);
    QObject::connect(_ui->actionNew, SIGNAL(triggered()), this, SLOT(print_status()));
    QObject::connect(_ui->actionParameters, SIGNAL(triggered()), this, SLOT(print_circle()));
}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _scene;
}

void MainWindow::DrawShelf(QColor &color)
{
    QImage *image = new QImage(":/Background/parquet.jpg");
    QBrush *brush = new QBrush(*image);
    _scene->setBackgroundBrush(*brush);
    QPen pen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    float size = (float) _sizeboard;
    _border = 25;
    float height = _ui->gameboard->geometry().height();
    float width = _ui->gameboard->geometry().width();
    float heightb = height - 2 * _border;
    float widthb = width - 2 * _border;
    _refh = heightb / (size - 1);
    _refw = widthb / (size - 1);
    for (int i = 0; i < size; i++)
    {
        QLine v_line(_border + i * _refw, _border,
                     _border + i * _refw, heightb + _border);
        QLine h_line(_border, _border + i * _refh,
                     widthb + _border, _border + i * _refh);
        _ui->gameboard->scene()->addLine(h_line, pen);
        _ui->gameboard->scene()->addLine(v_line, pen);
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
    QGraphicsScene *canvas = _ui->gameboard->scene();
    QAbstractGraphicsShapeItem* i = canvas->addEllipse(QRectF(0,0,8,8), pen);
    i->setBrush(color);
    i->setPos(x - 4, y - 4);
}

void MainWindow::DrawPiece(int x, int y)
{
    QGraphicsScene *canvas = _ui->gameboard->scene();
    QAbstractGraphicsShapeItem* i = canvas->addEllipse(QRectF(0, 0, 30, 30));
    //i->setFlag(QGraphicsItem::ItemIsMovable);
    i->setPen(Qt::NoPen);
    i->setBrush( QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8) );
    i->setPos(x - 15, y - 15);
}

void MainWindow::DrawBoard()
{
    // clear scene
    // parcours de _game->getgameBoard() en x, y
    // en fonction du pion,
    // Drawpiece(x, y)
    // emit signal si possible.
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    _scene = new QGraphicsScene(5, 5,
                                _ui->gameboard->geometry().width() - 5,
                                _ui->gameboard->geometry().height() - 5);
    _ui->gameboard->setScene(_scene);
    _ui->gameboard->scene()->clear();
    QColor color(Qt::black);
    DrawShelf(color);
    update();
    QWidget::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    float casex = (event->pos().x() - _border) / _refw;
    float casey = (event->pos().y() - _border) / _refh;

    std::cout << "casex = " << casex << std::endl <<
                 "casey = " << casey << std::endl;
    std::cout << "cadre1 = " << ((casex * _refw + _border) - 10 ) << std::endl <<
                 "cadre2 = " << ((casex * _refw + _border) + 10 ) << std::endl;
    if ((event->pos().x() > (casex * _refw + _border) - 10 ) &&
        (event->pos().x() < (casex * _refw + _border) + 10 ))
       this->DrawPiece((casex * _refw + _border),
                       (event->pos().y()));

    std::cout << "x = " << event->pos().x() << std::endl <<
                 "y = " << event->pos().y() << std::endl <<
                 "height= " << _ui->gameboard->geometry().height() << std::endl <<
                 "width= " << _ui->gameboard->geometry().width() << std::endl <<
                 "_refh= " << _refh << std::endl <<
                 "_refw= " << _refw << std::endl;
}

void MainWindow::print_status()
{
    _ui->statusBar->showMessage("ready to go");
}

void MainWindow::print_circle()
{
}
