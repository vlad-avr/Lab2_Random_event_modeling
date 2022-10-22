#ifndef RANDEVENT_H
#define RANDEVENT_H
#include <iostream>
struct REvent{
public:
    std::string name;
    double val;
    double possib;

    REvent(){val = 0; possib = 0;}
    REvent(REvent* copy_event){this->name = copy_event->name; this->val = copy_event->val; this->possib = copy_event->possib;}
    REvent(std::string name, double val, double possib){this->name = name; this->val = val; this->possib = possib;}
};

#endif // RANDEVENT_H
