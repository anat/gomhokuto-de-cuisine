#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene * scene = new QGraphicsScene(this);
    std::cout << "height plateau: " << ui->gameboard->height() << std::endl;
    std::cout << "height plateau: " << ui->centralWidget->height() << std::endl;
    std::cout << "height plateau: " << this->centralWidget()->height() << std::endl;
    std::cout << "width plateau: " << ui->gameboard->width() << std::endl;
    std::cout << "width plateau: " << ui->centralWidget->width() << std::endl;
    ui->gameboard->setScene(scene);
    DrawCadre();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawCadre()
{
    float size = 20;
    float height = ui->centralWidget->height() - 24; //ui->gameboard->height();
    float width = ui->centralWidget->width() - 24;   //ui->gameboard->width();
    float refh = height / size;
    float refw = width / size;
    std::cout << "height: " << height << std::endl;
    std::cout << "width: " << width << std::endl;
//*
    for (int i = 1; i < size; i++)
    {
        QLine l1(i * refh, refh, i * refh, width - refh);
        QLine l2(refh , i * refw, height - refh, i * refw);
        ui->gameboard->scene()->addLine(l1);
        ui->gameboard->scene()->addLine(l2);
    }
//*/
}
