#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(print_status()));
    QObject::connect(ui->actionParameters, SIGNAL(triggered()), this, SLOT(print_circle()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::DrawCadre(QColor &color)
{
    QImage *image = new QImage(":/Background/parquet.jpg");
    QBrush *brush = new QBrush(*image);
    scene->setBackgroundBrush(*brush);
    QPen pen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    float size = 19;
    border = 25;
    float height = ui->gameboard->geometry().height();
    float width = ui->gameboard->geometry().width();
    float heightb = height - 2 * border;
    float widthb = width - 2 * border;
    refh = heightb / (size - 1);
    refw = widthb / (size - 1);
    for (int i = 0; i < size; i++)
    {
        QLine v_line(border + i * refw, border,
                     border + i * refw, heightb + border);
        QLine h_line(border, border + i * refh,
                     widthb + border, border + i * refh);
        ui->gameboard->scene()->addLine(h_line, pen);
        ui->gameboard->scene()->addLine(v_line, pen);
    }
    Drawrepere(color, border + 3 * refw, border + 3 * refh);
    Drawrepere(color, border + 3 * refw, border + 9 * refh);
    Drawrepere(color, border + 3 * refw, border + 15 * refh);
    Drawrepere(color, border + 9 * refw, border + 3 * refh);
    Drawrepere(color, border + 9 * refw, border + 9 * refh);
    Drawrepere(color, border + 9 * refw, border + 15 * refh);
    Drawrepere(color, border + 15 * refw, border + 3 * refh);
    Drawrepere(color, border + 15 * refw, border + 9 * refh);
    Drawrepere(color, border + 15 * refw, border + 15 * refh);

}

void MainWindow::Drawrepere(QColor &color, int x, int y)
{
    QPen pen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QGraphicsScene *canvas = ui->gameboard->scene();
    QAbstractGraphicsShapeItem* i = canvas->addEllipse(QRectF(0,0,8,8), pen);
    i->setBrush(color);
    i->setPos(x - 4, y - 4);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    scene = new QGraphicsScene(5, 5,
                                ui->gameboard->geometry().width() - 5,
                                ui->gameboard->geometry().height() - 5);
    ui->gameboard->setScene(scene);
    ui->gameboard->scene()->clear();
    QColor color(Qt::black);
    DrawCadre(color);
    update();
    QWidget::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    float casex = (event->pos().x() - border) / refw;
    float casey = (event->pos().y() - border) / refh;

    std::cout << "casex = " << casex << std::endl <<
                 "casey = " << casey << std::endl;
    std::cout << "cadre1 = " << ((casex * refw + border) - 10 ) << std::endl <<
                 "cadre2 = " << ((casex * refw + border) + 10 ) << std::endl;
    if ((event->pos().x() > (casex * refw + border) - 10 ) &&
        (event->pos().x() < (casex * refw + border) + 10 ))
       this->DrawPiece((casex * refw + border),
                       (event->pos().y()));

    std::cout << "x = " << event->pos().x() << std::endl <<
                 "y = " << event->pos().y() << std::endl <<
                 "height= " << ui->gameboard->geometry().height() << std::endl <<
                 "width= " << ui->gameboard->geometry().width() << std::endl <<
                 "refh= " << refh << std::endl <<
                 "refw= " << refw << std::endl;
}

void MainWindow::DrawPiece(int x, int y)
{
    QGraphicsScene *canvas = ui->gameboard->scene();
    QAbstractGraphicsShapeItem* i = canvas->addEllipse(QRectF(0, 0, 30, 30));
    //i->setFlag(QGraphicsItem::ItemIsMovable);
    i->setPen(Qt::NoPen);
    i->setBrush( QColor(qrand()%32*8,qrand()%32*8,qrand()%32*8) );
    i->setPos(x - 15, y - 15);
}

void MainWindow::print_status()
{
    ui->statusBar->showMessage("ready to go");
}

void MainWindow::print_circle()
{
}
