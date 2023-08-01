#include "runner.h"

Runner::Runner(std::string Name, const int StartId, double time) : Athlete(Name, StartId), time(time)
{

}

double Runner::getTime() const
{
    return time;
}

void Runner::setTime(double newTime)
{
    time = newTime;
}

Trainer *Runner::getTrainer() const
{
    return trainer;
}

void Runner::setTrainer(Trainer *newTrainer)
{
    trainer = newTrainer;
}
