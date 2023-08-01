#ifndef SWIMMER_H
#define SWIMMER_H

#include <string>
#include "trainer.h"

class Swimmer : public Athlete
{
public:
    Swimmer(std::string Name, const int StartId, double time);

    double getTime() const;
    void setTime(double newTime);

    Trainer *getTrainer() const;
    void setTrainer(Trainer *newTrainer);

private:
    double time;

    Trainer* trainer = nullptr;
};

#endif // SWIMMER_H
