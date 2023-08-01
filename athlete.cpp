#include "athlete.h"

std::string& Athlete::GetName() {
    return this->Name;
}

const int Athlete::GetStartId() {
    return this->StartId;
}

void Athlete::SetName(std::string Name) {
    this->Name = Name;
}
