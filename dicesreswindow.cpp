#include "dicesreswindow.h"
#include "ui_dicesreswindow.h"

DicesResWindow::DicesResWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DicesResWindow)
{
    ui->setupUi(this);
}

DicesResWindow::~DicesResWindow()
{
    delete ui;
}
