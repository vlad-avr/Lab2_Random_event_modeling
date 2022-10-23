#include "dicesmanual.h"
#include "ui_dicesmanual.h"
#include <iostream>
#include "probexp.h"
#include "RandEvent.h"
#include <QMessageBox>


DicesManual::DicesManual(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DicesManual)
{
    ui->setupUi(this);
    exp = new ProbExp();
}

DicesManual::~DicesManual()
{
    delete ui;
}

void DicesManual::on_AddEventButton_clicked()
{
    std::string name = ui->event_name_lineE->text().toStdString();
    bool is_ok = true;
    double value = ui->event_value_lineE->text().toDouble(&is_ok);
    double possib = ui->event_prob_lineE->text().toDouble(&is_ok);
    if(is_ok){
        exp->add(exp->size(), REvent(name, value, possib));
        ui->listWidget->addItem(QString::fromStdString(name + "  " + std::to_string(value) + "  " + std::to_string(possib)));
    }
    else{
        QMessageBox::warning(this, "Add event", "ERROR: value or probability is not a number or written incorrectly!");
    }
    ui->event_name_lineE->clear();
    ui->event_value_lineE->clear();
    ui->event_prob_lineE->clear();
    ui->listWidget->setCurrentRow(0);
}



void DicesManual::on_EditEventButton_clicked()
{
    ui->EditBox->setEnabled(true);
    unsigned int i = ui->listWidget->currentRow();
    REvent event = exp->get(i);
    ui->edit_name_LineE->insert(QString::fromStdString(event.name));
    ui->edit_value_LineE->insert(QString::fromStdString(std::to_string(event.val)));
    ui->edit_prob_LineE->insert(QString::fromStdString(std::to_string(event.possib)));
}


void DicesManual::on_RemoveEventButton_clicked()
{
    exp->remove(ui->listWidget->currentRow());
    ui->listWidget->clear();
    for(int i = 0; i < exp->size(); i++){
        ui->listWidget->addItem(QString::fromStdString(exp->get(i).name + "  " + std::to_string(exp->get(i).val) + "  " + std::to_string(exp->get(i).possib)));
    }
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_EditButton_clicked()
{
    unsigned int i = ui->listWidget->currentRow();
    REvent event = exp->get(i);
    std::string name = ui->edit_name_LineE->text().toStdString();
    bool is_ok = true;
    double value = ui->edit_value_LineE->text().toDouble(&is_ok);
    double possib = ui->edit_prob_LineE->text().toDouble(&is_ok);
    if(is_ok){
        exp->set(i, REvent(name, value, possib));
        ui->listWidget->clear();
        for(int j = 0; j < exp->size(); j++){
            ui->listWidget->addItem(QString::fromStdString(exp->get(j).name + "  " + std::to_string(exp->get(j).val) + "  " + std::to_string(exp->get(j).possib)));
        }
    }
    else{
        QMessageBox::warning(this, "Edit event", "ERROR: value or probability is not a number or written incorrectly!");
    }
    ui->EditBox->setEnabled(false);
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_ComputeButton_clicked()
{
    const double eps = 0.00001;
    double exp_prob = 0;
    for(int i = 0; i < exp->size(); i++){
        exp_prob += exp->get(i).possib;
    }
    if(exp_prob + eps > 1 && exp_prob - eps < 1){
        QMessageBox::information(this, "Balls", "Gay website");
    }
    else{
        QMessageBox::warning(this, "Probability experiment", "ERROR: Overall sum of possibilities of all events is not equal to 1, consider changing possibilities in your events");
        ui->listWidget->setCurrentRow(0);
    }

}

