#ifndef MYSPORTS_H
#define MYSPORTS_H

#include "trainer.h"
#include "athlete.h"
#include "runner.h"
#include "swimmer.h"
#include <vector>
#include <string>
#include <mutex>

struct AthleteParseResult {
    std::string name;
    int startId;
    double time;
    int license;

    int type;
};

struct TrainerParseResult {
    std::string name;
    int license;

    std::vector<int> athleteIds;
};

class MySports
{
public:
    MySports();
    ~MySports();

    void addSwimmer(std::string Name, const int StartId, double time);
    void addRunner(std::string Name, const int StartId, double time);

    void addTrainer(std::string Name, const int License);

    Athlete* getAthlete(const int Id);
    Trainer* getTrainer(const int License);

    std::vector<Athlete*>& getAthletes();
    std::vector<Trainer*>& getTrainers();

    void save(std::string fileName);
    void load(std::string fileName);

private:
    std::vector<Athlete*> athletes;
    std::vector<Trainer*> trainers;

    std::mutex mutex;
};

#endif // MYSPORTS_H
