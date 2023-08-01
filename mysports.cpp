#include "mysports.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#define MODE_RUNNER 0
#define MODE_SWIMMER 1
#define MODE_TRAINER 2

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

std::vector<Trainer *> &MySports::getTrainers()
{
    return this->trainers;
}

void MySports::save(std::string fileName)
{

}

void MySports::load(std::string fileName)
{
    //Parsing this file is shitty
    std::ifstream file(fileName);

    std::vector<AthleteParseResult*> parseResults;
    std::vector<TrainerParseResult*> trainerParseResults;

    int i = 1;

    int mode = -1;

    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string property;

        if(line.rfind("# Runner", 0) == 0) {
            mode = MODE_RUNNER;
        } else if(line.rfind("# Swimmer") == 0) {
            mode = MODE_SWIMMER;
        } else if(line.rfind("# Trainer") == 0) {
            mode = MODE_TRAINER;
        }

        //Skip if comment or metadata
        if(line.rfind("#", 0) == 0) continue;

        switch(mode) {
        case 0:
        case 1:
        {
            std::string name;
            int startId;
            double time;
            int licenseTrainer;

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            name = property;

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            if(!std::all_of(property.begin(), property.end(), ::isdigit)) {
                std::cout << "StartID muss eine Nummer sein!" << std::endl;
                break;
            }
            startId = stoi(property);

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            try {
                time = stod(property);
            } catch(std::invalid_argument& e) {
                std::cout << "time muss eine Nummer sein!" << std::endl;
                break;
            }

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing s on line " << i << std::endl;
                continue;
            }

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            if(!std::all_of(property.begin(), property.end(), ::isdigit)) {
                std::cout << "license muss eine Nummer sein!" << std::endl;
                break;
            }
            licenseTrainer = stoi(property);

            //Dirty solution because Trainers are not known yet
            AthleteParseResult* parseResult = new AthleteParseResult {.name = name, .startId = startId, .time = time, .license = licenseTrainer, .type = mode};

            parseResults.push_back(parseResult);
            break;
        }
        case 2:
            std::string name;
            int license;

            std::vector<int> athleteIds;

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            name = property;

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            if(!std::all_of(property.begin(), property.end(), ::isdigit)) {
                std::cout << "Lizenz muss eine Nummer sein!" << std::endl;
                break;
            }
            license = stoi(property);

            if(!std::getline(ss, property, ' ')) {
                std::cout << "Missing property on line " << i << std::endl;
                continue;
            }

            while(std::getline(ss, property, ' ')) {
                if(!std::all_of(property.begin(), property.end(), ::isdigit)) {
                    std::cout << "Athletes muss eine Nummer sein!" << std::endl;
                    break;
                }

                int athleteId = stoi(property);

                //This is redundant

                athleteIds.push_back(athleteId);
            }
            TrainerParseResult* parseResult = new TrainerParseResult {.name = name, .license = license, .athleteIds = athleteIds};

            trainerParseResults.push_back(parseResult);
        }

        i++;
    }

    file.close();

    for(AthleteParseResult* parseResult : parseResults) {
        if(parseResult->type == 0) {
            this->addRunner(parseResult->name, parseResult->startId, parseResult->time);
        } else {
            this->addSwimmer(parseResult->name, parseResult->startId, parseResult->time);
        }
    }

    for(TrainerParseResult* parseResult : trainerParseResults) {
        this->addTrainer(parseResult->name, parseResult->license);
    }

    for(AthleteParseResult* parseResult : parseResults) {
        Athlete* athlete = this->getAthlete(parseResult->startId);
        Trainer* trainer = this->getTrainer(parseResult->license);

        if(athlete == nullptr) {
            std::cerr << "Athlete " << parseResult->startId << " not found, inconsistency detected, exiting...";
            return;
        }

        if(trainer == nullptr) {
            std::cerr << "Trainer " << parseResult->license << " not found, inconsistency detected, exiting...";
            return;
        }

        if(parseResult->type == 0) {
            Runner* runner = dynamic_cast<Runner*>(athlete);

            runner->setTrainer(trainer);
        } else {
            Swimmer* swimmer = dynamic_cast<Swimmer*>(athlete);

            swimmer->setTrainer(trainer);
        }

        delete parseResult;
    }

    for(TrainerParseResult* parseResult : trainerParseResults) {
        Trainer* trainer = this->getTrainer(parseResult->license);

        if(trainer == nullptr) {
            std::cerr << "Trainer " << parseResult->license << " not found, inconsistency detected, exiting...";
            return;
        }

        for(std::vector<int>::iterator it = parseResult->athleteIds.begin(); it != parseResult->athleteIds.end(); it++) {
            Athlete* athlete = this->getAthlete(*it);

            if(athlete == nullptr) {
                std::cerr << "Athlete " << *it << " not found, inconsistency detected, exiting...";
                return;
            }

            trainer->addAthlete(athlete);
        }

        delete parseResult;
    }

}


