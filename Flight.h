/*
This Flight class manages flight information, specifically the departure and
destination locations. It has constructors for easy initialization and methods
to set and retrieve this information. The class is intended for use in an 
airline scheduling application.

Copyright by Colin Kula, 11/15/2023
*/

#ifndef FLIGHT_H
#define FLIGHT_H
#include<string>

class Flight {
 private:
        std::string from;
        std::string to;
 public:
        Flight();
        Flight(std::string from, std::string to);
        void setFlight(std::string from, std::string to);
        std::string getFrom();
        std::string getTo();
};
#endif  // FLIGHT_H_
