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
    double get_omega();
    REvent get_rand_event();
    void qsort(bool (*comp)(REvent*, REvent*)){
        qsort_rec(comp, &events[0], &events[events.size() - 1]);
    }
    std::vector<REvent> compute(unsigned int N);
    //void print();

private:
    void swap(REvent* p, REvent* q) {
            REvent temp;
            temp = *q; *q = *p; *p = temp;
    }

    void qsort_rec(bool (*comp)(REvent*, REvent*), REvent* beg, REvent* end) {
        REvent r_pivot_str, * l_pointer, * r_pointer;
        if ((end - beg == 1) && !comp(beg, end)) {
            swap(beg, end);
        }
        else if (end - beg > 1) {
            l_pointer = beg;
            r_pointer = end - 1;
            r_pivot_str = *end;
            while (l_pointer < r_pointer) {
                if (!comp(r_pointer, &r_pivot_str)) {
                    r_pointer--;
                }
                else {
                    if (!comp(l_pointer, &r_pivot_str)) {
                        swap(l_pointer, r_pointer);
                    }
                    l_pointer++;
                }
            }
            if (comp(l_pointer, &r_pivot_str)) {
                r_pointer++;
            }
            swap(r_pointer, end);
            qsort_rec(comp, beg, r_pointer - 1);
            qsort_rec(comp, r_pointer + 1, end);
        }
    }
    std::vector<REvent> events;

};

#endif // PROBEXP_H
