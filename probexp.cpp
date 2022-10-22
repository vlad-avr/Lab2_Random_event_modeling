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

void ProbExp::set(unsigned int id, std::string name, double val, double possib)
{
    assert(id <= this->size());
    std::vector<REvent>::iterator it = events.begin() + id;
    events.insert(it, REvent(name, val, possib));
}

double ProbExp::get_M(int power)
{
    int size = this->size();
    double M = 0;
    for(int i = 0; i < size; i++){
        M += pow((events[i].val), power) * (events[i].possib);
    }
    return M;
}

double ProbExp::get_D()
{
    return (get_M() - get_M(2));
}

REvent ProbExp::get_rand_event()
{
    int size = this->size();
    assert(size != 0);
    double r_num = ((rand() % size) + 1) / size;
    double cur_diap = 0;
    for(int i = 0; i < size; i++){
        cur_diap += events[i].possib;
        if(r_num <= cur_diap){return events[i];}
    }
    // should not return this;
    return REvent("0", 0, 0);
}

//void ProbExp::print()
//{
//    QListWidget *qlist = new QListWidget();
//    int size = this->size();
//    for(int i = 0; i < size; i++){
//        qlist->addItem(QString::number(this->get(i).val) + " : " + QString::number(this->get(i).possib));
//    }
//}

ProbExp::ProbExp(QObject *parent)
    : QObject{parent}
{

}
