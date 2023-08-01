#ifndef RUNNER_H
#define RUNNER_H

#include <string>
#include "trainer.h"

class Runner : public Athlete
{
public:
    Runner(std::string Name, const int StartId, double time);

    double getTime() const;
    void setTime(double newTime);

    Trainer *getTrainer() const;
    void setTrainer(Trainer *newTrainer);

private:
    double time;

    Trainer* trainer;
};

#endif // RUNNER_H
