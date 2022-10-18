#include "probexp.h"
#include <iostream>
#include <vector>
#include <cassert>

ProbExp::ProbExp(ProbExp *copy_exp)
{
    int size = copy_exp->size();
    for(int i = 0; i < size; i++){
        this->set()
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

ProbExp::ProbExp(QObject *parent)
    : QObject{parent}
{

}
