#include "dicesmanual.h"
#include "ui_dicesmanual.h"
#include <iostream>
#include "probexp.h"
#include "RandEvent.h"
#include <QMessageBox>
#include <time.h>
#include <fstream>

DicesManual::DicesManual(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DicesManual)
{
    ui->setupUi(this);
    ui->number_of_exp_lineE->insert("1");
    exp = new ProbExp();
    seed = time(NULL);
    ui->seed_lineE->insert(QString::fromStdString(std::to_string(seed)));
}

DicesManual::~DicesManual()
{
    delete exp;
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
    ui->event_name_lineE->insert("Event1");
    ui->event_value_lineE->insert("0.0");
    ui->event_prob_lineE->insert("0.0");
    ui->listWidget->setCurrentRow(0);
}

bool possib_comp(REvent *r1, REvent* r2)
{
    if(r1->possib >= r2->possib){
        return true;
    }
    else{
        return false;
    }
}

bool val_comp(REvent* r1, REvent* r2)
{
    if(r1->val >= r2->val){
        return true;
    }
    else{
        return false;
    }
}

bool str_comp(REvent* r1, REvent* r2)
{
    if(r1->name.length() < r2->name.length()){
        return true;
    }
    else if(r1->name.length() > r2->name.length()){
        return false;
    }
    else{
        int len = r1->name.length();
        for(int i = 0; i < len; i++){
            if(r1->name[i] < r2->name[i]){
                return true;
            }
            else if(r1->name[i] > r2->name[i]){
                return false;
            }
            else{
                continue;
            }
        }
        return true;
    }
}

void DicesManual::sort(bool (*comp)(REvent *, REvent *))
{
    exp->qsort(comp);
}

void DicesManual::on_EditEventButton_clicked()
{
    if(ui->listWidget->count() == 0){
        QMessageBox::warning(this, "Edit", "You have no items to edit, lol");
        return;
    }
    ui->EditBox->setEnabled(true);
    unsigned int i = ui->listWidget->currentRow();
    REvent event = exp->get(i);
    ui->edit_name_LineE->insert(QString::fromStdString(event.name));
    ui->edit_value_LineE->insert(QString::fromStdString(std::to_string(event.val)));
    ui->edit_prob_LineE->insert(QString::fromStdString(std::to_string(event.possib)));
}


void DicesManual::on_RemoveEventButton_clicked()
{
    if(ui->listWidget->count() == 0){
        QMessageBox::warning(this, "Edit", "You have no items to remove, lol");
        return;
    }
    exp->remove(ui->listWidget->currentRow());
    ui->listWidget->clear();
    for(int i = 0; i < exp->size(); i++){
        ui->listWidget->addItem(QString::fromStdString(exp->get(i).name + "  " + std::to_string(exp->get(i).val) + "  " + std::to_string(exp->get(i).possib)));
    }
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_EditButton_clicked()
{
    if(ui->listWidget->count() == 0){
        QMessageBox::warning(this, "Edit", "You have no items to edit, lol");
        return;
    }
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
    ui->edit_name_LineE->clear();
    ui->edit_value_LineE->clear();
    ui->edit_prob_LineE->clear();
    ui->EditBox->setEnabled(false);
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_ComputeButton_clicked()
{
    const double eps = 0.00001;
    double exp_prob = 0;
    bool is_ok = true;
    for(int i = 0; i < exp->size(); i++){
        exp_prob += exp->get(i).possib;
    }

    seed = ui->seed_lineE->text().toInt(&is_ok);
    if(!is_ok){
        QMessageBox::warning(this, "Seed", "ERROR: The seed for random generation is invalid");
        return;
    }
    srand(seed);
    if(exp_prob + eps > 1 && exp_prob - eps < 1){
        int N = ui->number_of_exp_lineE->text().toInt(&is_ok);
        if(is_ok){
            dr_wind = new DicesResWindow(this);
            dr_wind->show();
            dr_wind->set_ui(exp, N);
        }
        else{
            QMessageBox::warning(this, "Compute", "ERROR: Please enter a natural number (NOT 0)");
        }
    }
    else{
        QMessageBox::warning(this, "Probability experiment", "ERROR: Overall sum of possibilities of all events is not equal to 1, consider changing possibilities in your events");  
    }
     ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_nameSortButton_clicked()
{
    if(exp->size() == 0){
        QMessageBox::information(this, "Sort", "You have no events to sort");
        return;
    }
    sort(str_comp);
    ui->listWidget->clear();
    for(int i = 0; i < exp->size(); i++){
        ui->listWidget->addItem(QString::fromStdString(exp->get(i).name + "  " + std::to_string(exp->get(i).val) + "  " + std::to_string(exp->get(i).possib)));
    }
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_valueSortButton_clicked()
{
    if(exp->size() == 0){
        QMessageBox::information(this, "Sort", "You have no events to sort");
        return;
    }
    sort(val_comp);
    ui->listWidget->clear();
    for(int i = 0; i < exp->size(); i++){
        ui->listWidget->addItem(QString::fromStdString(exp->get(i).name + "  " + std::to_string(exp->get(i).val) + "  " + std::to_string(exp->get(i).possib)));
    }
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_possibSortButton_clicked()
{
    if(exp->size() == 0){
        QMessageBox::information(this, "Sort", "You have no events to sort");
        return;
    }
    sort(possib_comp);
    ui->listWidget->clear();
    for(int i = 0; i < exp->size(); i++){
        ui->listWidget->addItem(QString::fromStdString(exp->get(i).name + "  " + std::to_string(exp->get(i).val) + "  " + std::to_string(exp->get(i).possib)));
    }
    ui->listWidget->setCurrentRow(0);
}


void DicesManual::on_saveSeedButton_clicked()
{
//    FILE* seed_file;
//    seed_file = fopen("seed.bin", "rb");
//    fseek(seed_file, 0, SEEK_END);
//    fflush(seed_file);
      std::ofstream file("seed.bin", std::ios::binary|std::ios::app);
      bool is_ok = true;
      seed = ui->seed_lineE->text().toInt(&is_ok);
      if(is_ok){
          file.write((char*)&seed, sizeof(int));
          QMessageBox::information(this, "Save seed", "Seed was saved successfully!");
      }
      else{
          QMessageBox::warning(this, "Save seed", "ERROR: seed is of wrong type (desired type - int)");
      }
      file.close();
}


void DicesManual::on_loadSeedButton_clicked()
{
    ui->LoadBox->setEnabled(true);
    std::ifstream file("seed.bin", std::ios::binary);
    std::vector<int> seed_vec;
    int t;
    ui->load_listWidget->clear();
    while(file.read((char*)&t, sizeof(int))){
      //  QMessageBox::information(this, "BALLS", QString::fromStdString(std::to_string(t)));
        seed_vec.push_back(t);
        ui->load_listWidget->addItem(QString::fromStdString(std::to_string(t)));
    }
    file.close();
    ui->load_listWidget->setCurrentRow(0);
}


void DicesManual::on_loadButton_clicked()
{
    if(ui->load_listWidget->count() == 0){
        QMessageBox::warning(this, "Load seed", "ERROR: you have no seeds to load");
        return;
    }
    ui->seed_lineE->clear();
    ui->seed_lineE->insert(ui->load_listWidget->currentItem()->text());
    ui->load_listWidget->setCurrentRow(0);
}


void DicesManual::on_removeSeedButton_clicked()
{
    if(ui->load_listWidget->count() == 0){
        QMessageBox::warning(this, "Remove seed", "ERROR: you have no seeds to remove");
        return;
    }
    std::vector<int> seed_vec;
    int len = ui->load_listWidget->count();
    int del_id = ui->load_listWidget->currentRow();
    for(int i = 0; i < len; i++){
        if(i != del_id){
            ui->load_listWidget->setCurrentRow(i);
            seed_vec.push_back(ui->load_listWidget->currentItem()->text().toInt());
        }
    }
    ui->load_listWidget->clear();
    std::ofstream file("seed.bin", std::ios::binary|std::ios::trunc);
    for(int i = 0; i < seed_vec.size(); i++){
        ui->load_listWidget->addItem(QString::fromStdString(std::to_string(seed_vec[i])));
        file.write((char*)&seed_vec[i], sizeof(int));
    }
    file.close();
}

