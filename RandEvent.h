#ifndef RANDEVENT_H
#define RANDEVENT_H
struct REvent{
public:
    int val;
    double possib;

    REvent(){val = 0; possib = 0;}
    REvent(REvent* copy_event){this->val = copy_event->val; this->possib = copy_event->possib;}
    REvent(int val, double possib){this->val = val; this->possib = possib;}
};

#endif // RANDEVENT_H
