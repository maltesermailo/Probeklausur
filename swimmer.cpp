#include "swimmer.h"

Swimmer::Swimmer(std::string Name, const int StartId, double time) : Athlete(Name, StartId), time(time)
{

}

double Swimmer::getTime() const
{
    return time;
}

void Swimmer::setTime(double newTime)
{
    time = newTime;
}

Trainer *Swimmer::getTrainer() const
{
    return trainer;
}

void Swimmer::setTrainer(Trainer *newTrainer)
{
    trainer = newTrainer;
}
