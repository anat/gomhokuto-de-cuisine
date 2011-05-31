#include "finalstate.hpp"
#include "ui_finalstate.h"

FinalState::FinalState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinalState)
{
    ui->setupUi(this);
    QObject::connect(ui->AgainButton, SIGNAL(clicked()), this, SLOT(AgainButton()));
    QObject::connect(ui->NewButton, SIGNAL(clicked()), this, SLOT(NewButton()));
    QObject::connect(ui->CloseButton, SIGNAL(clicked()), this, SLOT(CloseButton()));
}

FinalState::~FinalState()
{
    delete ui;
}

void FinalState::AgainButton()
{
    emit SignalAgain();
    this->close();
}

void FinalState::NewButton()
{
    emit SignalNew();
    this->close();
}

void FinalState::CloseButton()
{
    emit SignalClose();
    this->close();
}
