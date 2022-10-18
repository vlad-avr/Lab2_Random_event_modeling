#ifndef PROBEXP_H
#define PROBEXP_H

#include <QObject>
#include <vector>
#include <RandEvent.h>
class ProbExp : public QObject
{
    Q_OBJECT
public:
    ProbExp(ProbExp* copy_exp);

    REvent get(unsigned int id);

    int size();
    void set(unsigned int id, REvent event);
    void set(unsigned int id, int val = 0, double possib = 0);

    explicit ProbExp(QObject *parent = nullptr);
private:
    std::vector<REvent> events;


signals:

};

#endif // PROBEXP_H
