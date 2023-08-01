#include "mysports.h"

MySports::MySports()
{

}

MySports::~MySports()
{
    for(std::vector<Athlete*>::iterator it = this->athletes.begin(); it != this->athletes.end(); it++) {
        delete (*it);
    }

    for(std::vector<Trainer*>::iterator it = this->trainers.begin(); it != this->trainers.end(); it++) {
        delete (*it);
    }
}

void MySports::addSwimmer(std::string Name, const int StartId, double time)
{
    mutex.lock();

    Swimmer* swimmer = new Swimmer(Name, StartId, time);

    this->athletes.push_back(swimmer);

    mutex.unlock();
}

void MySports::addRunner(std::string Name, const int StartId, double time)
{
    mutex.lock();

    Runner* runner = new Runner(Name, StartId, time);

    this->athletes.push_back(runner);

    mutex.unlock();
}

void MySports::addTrainer(std::string Name, const int License)
{
    mutex.lock();

    Trainer* trainer = new Trainer(Name, License);

    this->trainers.push_back(trainer);

    mutex.unlock();
}

Athlete *MySports::getAthlete(const int Id)
{
    mutex.lock();

    for(std::vector<Athlete*>::iterator it = this->athletes.begin(); it != this->athletes.end(); it++) {
        if((*it)->GetStartId() == Id) {
            mutex.unlock();

            return (*it);
        }
    }

    mutex.unlock();

    return nullptr;
}

Trainer *MySports::getTrainer(const int License)
{
    mutex.lock();

    for(std::vector<Trainer*>::iterator it = this->trainers.begin(); it != this->trainers.end(); it++) {
        if((*it)->getLicense() == License) {
            mutex.unlock();

            return (*it);
        }
    }

    mutex.unlock();

    return nullptr;
}

std::vector<Athlete *> &MySports::getAthletes()
{
    return this->athletes;
}

std::vector<Trainer *> MySports::getTrainers()
{
    return this->trainers;
}

void MySports::save(std::string fileName)
{

}

void MySports::load(std::string fileName)
{

}


