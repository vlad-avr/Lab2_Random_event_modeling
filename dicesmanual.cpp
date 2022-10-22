#include "dicesmanual.h"
#include "ui_dicesmanual.h"

DicesManual::DicesManual(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DicesManual)
{
    ui->setupUi(this);
}

DicesManual::~DicesManual()
{
    delete ui;
}
