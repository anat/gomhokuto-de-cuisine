#include "open.hpp"
#include "ui_open.h"

Open::Open(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Open)
{
    ui->setupUi(this);
}

Open::~Open()
{
    delete ui;
}
