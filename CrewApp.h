/*
The CrewApp class is the core component of an airline crew scheduling
application. It manages information about flights, crews, and unique flight
locations. The class includes methods for printing menus and various scheduling
related information, as well as functions for importing crew and flight data
from files. The class is designed to provide a user-friendly interface for 
interacting with and managing crew schedules.

Copyright by Colin Kula, 11/15/2023
*/

#ifndef CREWAPP_H
#define CREWAPP_H
#include <string>
#include <vector>
#include <set>
#include "Crew.h"
#include "Flight.h"

class CrewApp {
 private:
        std::vector<Flight> flights;
        std::vector<Crew> crews;
        std::set<std::string> uniqueFLocations;
        std::string crewfileName;
        std::string flightfileName;
 public:
        CrewApp();
        CrewApp(std::string crewfileName, std::string flightfileName);
        void PrintMenu();
        void PrintCrews();
        void PrintFlightsForCrew();
        void PrintCrewsForFlight();
        void PrintUniqueLocations();
        void ExecuteMenu(int opt);
        void ImportCrew();
        void ImportFlights();
        void FillUniqueFlights();
};
#endif  // CREWAPP_H_
