#ifndef TRAINER_H
#define TRAINER_H

#include "athlete.h"
#include <string>
#include <vector>

class Trainer
{
public:
    Trainer(std::string Name, const int License);

    void addAthlete(Athlete* athlete);
    void removeAthlete(Athlete* athlete);
    bool hasAthlete(Athlete* athlete);

    std::string getName() const;
    void setName(const std::string &newName);

    int getLicense() const;

private:
    std::string Name;
    const int License;

    std::vector<Athlete*> athletes;
};

#endif // TRAINER_H
