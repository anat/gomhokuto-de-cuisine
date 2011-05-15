#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene * scene;
    scene = new QGraphicsScene(0,
                               0,
                               ui->gameboard->geometry().width(),
                               ui->gameboard->geometry().height());
    ui->gameboard->setScene(scene);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawCadre()
{
    float size = 19;
    float height = ui->gameboard->geometry().height();
    float width = ui->gameboard->geometry().width();
    float refh = height / size;
    float refw = width / size;
    std::cout << "Draw cadre" << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "width: " << width << std::endl;
//*
    for (int i = 0; i < size; i++)
    {
        QLine h_line(100, 50 + i * refw,
                      i * refw, height - refh);
        QLine l1(i * refh, refh,
                 i * refh, height - refh);
       // QLine l2(refh , i * refw, height - refh, i * refw);
        ui->gameboard->scene()->addLine(h_line);
       // ui->gameboard->scene()->addLine(l2);
    }
//*/
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->gameboard->scene()->clear();
    DrawCadre();
    update();
    QWidget::resizeEvent(event);
}
