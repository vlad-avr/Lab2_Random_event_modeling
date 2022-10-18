#include "probexp.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <QListWidget>
#include <QString>

ProbExp::ProbExp(ProbExp *copy_exp)
{
    int size = copy_exp->size();
    for(int i = 0; i < size; i++){
        this->set(i, copy_exp->get(i));
    }
}

REvent ProbExp::get(unsigned int id)
{
    assert(id < this->size());
    return events[id];
}

int ProbExp::size()
{
    return events.size();
}

void ProbExp::set(unsigned int id, REvent event)
{
    assert(id <= this->size());
    std::vector<REvent>::iterator it = events.begin() + id;
    events.insert(it, event);
}

void ProbExp::set(unsigned int id, int val, double possib)
{
    assert(id <= this->size());
    std::vector<REvent>::iterator it = events.begin() + id;
    events.insert(it, REvent(val, possib));
}

void ProbExp::print()
{
    QListWidget *qlist = new QListWidget();
    int size = this->size();
    for(int i = 0; i < size; i++){
        qlist->addItem(QString::number(this->get(i).val) + " : " + QString::number(this->get(i).possib));
    }
}

ProbExp::ProbExp(QObject *parent)
    : QObject{parent}
{

}
