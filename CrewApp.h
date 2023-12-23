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
