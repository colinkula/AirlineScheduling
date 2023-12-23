/*
This program defines a Crew class with attributes for a crew member's name and
schedule. It provides functions to set and retrieve these attributes. This
program serves as a foundational component for handling crew information in a
larger system.

Copyright by Colin Kula, 11/15/2023
*/

#include "Crew.h"
#include <iostream>
#include <string>

/*
This constructor sets the name and schedule attributes to default values.
*/
Crew::Crew() {
    this->name = "";
    this->schedule = "";
}

/*
This constructor sets the name and schedule attributes based on input 
parameters.
*/
Crew::Crew(std::string name, std::string schedule) {
    this->name = name;
    this->schedule = schedule;
}

/*
This setter function assigns the provided name to the name attribute of the 
Crew object.
*/
void Crew::setName(std::string name) {
    this->name = name;
}

/*
This setter function assigns the provided schedule to the schedule attribute of
the Crew object.
*/
void Crew::setSchedule(std::string schedule) {
    this->schedule = schedule;
}

/*
This getter function returns the name attribute of the Crew object.
*/
std::string Crew::getName() {
    return this->name;
}

/*
This getter function returns the schedule attribute of the Crew object.
*/
std::string Crew::getSchedule() {
    return this->schedule;
}
