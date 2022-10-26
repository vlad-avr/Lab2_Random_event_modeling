#include "dicesreswindow.h"
#include "ui_dicesreswindow.h"
#include "RandEvent.h"
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

void DicesResWindow::set_ui(ProbExp *exp, int N)
{
    std::vector<REvent> vec = exp->compute(N);
    double average_val = 0.0;
    for(int i = 0; i < N; i++){
        ui->listWidget->addItem(QString::fromStdString(std::to_string(i+1) + "  " + vec[i].name + "  " + std::to_string(vec[i].val) + "  " + std::to_string(vec[i].possib)));
        average_val += vec[i].val;
    }
    ui->M_lineE->insert(QString::fromStdString(std::to_string(exp->get_M())));
    ui->D_lineE->insert(QString::fromStdString(std::to_string(exp->get_D())));

    ui->prob_lineE->insert(QString::fromStdString(std::to_string(average_val / (double)vec.size())));

}
