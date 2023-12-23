#include "Crew.h"
#include <iostream>
#include <string>

// Implement the Crew member functions here
Crew::Crew() {
    this->name = "";
    this->schedule = "";
}

Crew::Crew(std::string name, std::string schedule) {
    this->name = name;
    this->schedule = schedule;
}

void Crew::setName(std::string name) {
    this->name = name;
}

void Crew::setSchedule(std::string schedule) {
    this->schedule = schedule;
}

std::string Crew::getName() {
    return this->name;
}

std::string Crew::getSchedule() {
    return this->schedule;
}

