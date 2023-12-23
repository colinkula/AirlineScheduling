/*
This program defines a Flight class with attributes for a flights to and
from locations. It provides functions to set and retrieve these attributes. 
This program serves as a foundational component for handling flight 
information in alarger system.

// Copyright by Colin Kula, 11/15/2023
*/

#include "Flight.h"

/*
This constructor sets the to and from attributes to default values.
*/
Flight::Flight() {
    this->from = "";
    this->to = "";
}

/*
This constructor sets the to and from attributes based on input parameters.
*/
Flight::Flight(std::string from, std::string to) {
    this->from = from;
    this->to = to;
}

/*
This setter function assigns the provided to and from attributes to the flight
object.
*/
void Flight::setFlight(std::string from, std::string to) {
    this->from = from;
    this->to = to;
}

/*
This getter function returns the from attribute of the flight object.
*/
std::string Flight::getFrom() {
    return this->from;
}

/*
This getter function returns the to attribute of the flight object.
*/
std::string Flight::getTo() {
    return this->to;
}
