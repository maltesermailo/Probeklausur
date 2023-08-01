#include "trainer.h"


Trainer::Trainer(std::string Name, const int License) : Name(Name), License(License)
{

}

void Trainer::addAthlete(Athlete *athlete)
{
    if(this->hasAthlete(athlete)) return;

    this->athletes.push_back(athlete);
}

void Trainer::removeAthlete(Athlete *athlete)
{
    std::vector<Athlete*>::iterator it;

    while(it != this->athletes.end()) {
        if((*it) == athlete) {
            //Athlete can be compared since Athlete objects are only created during initialization

            this->athletes.erase(it);
            return;
        }
    }
}

bool Trainer::hasAthlete(Athlete *athlete)
{
    std::vector<Athlete*>::iterator it;

    while(it != this->athletes.end()) {
        if((*it) == athlete) {
            return true;
        }
    }

    return false;
}

std::string Trainer::getName() const
{
    return Name;
}

void Trainer::setName(const std::string &newName)
{
    Name = newName;
}

int Trainer::getLicense() const
{
    return License;
}
