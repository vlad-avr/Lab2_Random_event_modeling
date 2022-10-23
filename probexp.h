#ifndef PROBEXP_H
#define PROBEXP_H


#include <vector>
#include <RandEvent.h>
class ProbExp
{

public:
    ProbExp(ProbExp* copy_exp);
    ProbExp();
    REvent get(unsigned int id);

    int size();
    void add(unsigned int id, REvent event);
    void add(unsigned int id, std::string name, double val = 0, double possib = 0);
    void set(unsigned int id, REvent event);
    void set(unsigned int id, std::string name, double val = 0, double possib = 0);
    void remove(unsigned int id);
    double get_M(int power = 1);
    double get_D();
    REvent get_rand_event();
    //void print();

private:
    std::vector<REvent> events;

};

#endif // PROBEXP_H
