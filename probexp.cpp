#include "probexp.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <random>

ProbExp::ProbExp(ProbExp *copy_exp)
{
    int size = copy_exp->size();
    for(int i = 0; i < size; i++){
        this->set(i, copy_exp->get(i));
    }
}

ProbExp::ProbExp(){}

REvent ProbExp::get(unsigned int id)
{
    assert(id < this->size());
    return events[id];
}

int ProbExp::size()
{
    return events.size();
}

void ProbExp::add(unsigned int id, REvent event)
{
    assert(id <= this->size());
    std::vector<REvent>::iterator it = events.begin() + id;
    events.insert(it, event);
}

void ProbExp::add(unsigned int id, std::string name, double val, double possib)
{
    assert(id <= this->size());
    std::vector<REvent>::iterator it = events.begin() + id;
    events.insert(it, REvent(name, val, possib));
}

void ProbExp::set(unsigned int id, REvent event)
{
    assert(id < this->size());
    events[id] = event;
}

void ProbExp::set(unsigned int id, std::string name, double val, double possib)
{
    assert(id < this->size());
    events[id] = REvent(name, val, possib);
}


void ProbExp::remove(unsigned int id)
{
    assert(id < this->size());
    std::vector<REvent>::iterator it = this->events.begin() + id;
    this->events.erase(it);
}

double ProbExp::get_M(int power)
{
    int size = this->size();
    double omega = this->get_omega();
    double M = 0;
    for(int i = 0; i < size; i++){
        M += pow((events[i].val), power) * (events[i].possib/omega);
    }
    return M;
}

double ProbExp::get_D()
{
    return (get_M(2) - pow(get_M(1),2));
}

double ProbExp::get_omega()
{
    assert(this->size() > 0);
    int size = this->size();
    double res = 0;
    for(int i = 0; i < size; i++){
        res += events[i].possib;
    }
    return res;
}

REvent ProbExp::get_rand_event()
{
    int size = this->size();
    assert(size != 0);
    double r_num = ((double)rand()/RAND_MAX)*get_omega();
    double cur_diap = 0;
    for(int i = 0; i < size; i++){
        cur_diap += events[i].possib;
        if(r_num <= cur_diap){return events[i];}
    }

    return events[this->size() - 1];
}


std::vector<REvent> ProbExp::compute(unsigned int N)
{
    std::vector<REvent> res;
    for(int i = 0; i < N; i++){
       res.push_back(this->get_rand_event());
    }
    return res;
}

