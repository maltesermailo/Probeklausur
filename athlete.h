#ifndef ATHLETE_H
#define ATHLETE_H

#include <string>

class Athlete
{
public:
    Athlete();
    virtual ~Athlete() {}

    Athlete(std::string Name, const int StartId) : Name(Name), StartId(StartId) {}

    std::string& GetName();
    const int GetStartId();

    void SetName(std::string Name);

private:
    std::string Name;
    const int StartId;
};

#endif // ATHLETE_H
