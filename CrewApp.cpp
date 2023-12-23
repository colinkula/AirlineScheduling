#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "./CrewApp.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

/*
This function takes a string as input and iterates through each character,
converting it to its uppercase equivalent. The modified string is then 
returned.
*/
string stringToUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        str.at(i) = toupper(str.at(i));
    }
    return str;
}

/*
This function takes a string as input and iterates through each character,
converting it to its uppercase equivalent. The modified string is then 
returned.
*/
void pressEnter() {
    cout << "to continue, press enter..." << endl;
    cin.ignore();
    cin.get();
}

// Implement CrewApp function members here
CrewApp::CrewApp() {
    this->crewfileName = "";
    this->flightfileName = "";
    ImportCrew();
    ImportFlights();
    FillUniqueFlights();
}

CrewApp::CrewApp(std::string crewfileName, std::string flightfileName) {
    this->crewfileName = crewfileName;
    this->flightfileName = flightfileName;
    ImportCrew();
    ImportFlights();
    FillUniqueFlights();
}
void CrewApp::ImportCrew() {
    std::ifstream file(crewfileName);

    string line;
    while (getline(file, line)) {
        std::istringstream iss(line);

        string name, schedule;
        if (iss >> name >> schedule) {
            Crew member(name, schedule);
            crews.push_back(member);
        }
    }

    file.close();
}

void CrewApp::ImportFlights() {
    std::ifstream file(flightfileName);

    string line;
    while (getline(file, line)) {
        std::istringstream iss(line);

        string from, to;
        if (iss >> from >> to) {
            Flight flight(from, to);
            flights.push_back(flight);
        }
    }

    file.close();
}

void CrewApp::FillUniqueFlights() {
    for (int i = 0; i < flights.size(); i++) {
        if (uniqueFLocations.count(flights[i].getFrom()) == 0) {
            uniqueFLocations.insert(flights[i].getFrom());
        }

        if (uniqueFLocations.count(flights[i].getTo()) == 0) {
            uniqueFLocations.insert(flights[i].getTo());
        }
    }
}

void CrewApp::PrintMenu() {
    cout << "-----------------------------------" << endl
         << "Airline Crew Scheduling Application" << endl
         << "-----------------------------------" << endl
         << " 1 List crew names" << endl
         << " 2 List all flight locations" << endl
         << " 3 List crews for the flight" << endl
         << " 4 List flights for the crew" << endl
         << "-1 Exit" << endl
         << "-----------------------------------" << endl;
}

void CrewApp::PrintCrews() {
    //std::sort(crews.begin(), crews.end(), compareNames);
    cout << "---- Crew List ----" << endl;
    for (int i = 0; i < crews.size(); i++) {
        cout << crews[i].getName() << endl;
    }
    cout << endl;
}

void CrewApp::PrintUniqueLocations() {
    cout << "---- Flight Locations ----" << endl;
    for (const auto &element : uniqueFLocations) {
        cout << element << endl;
    }
    cout << endl;

}

void CrewApp::PrintCrewsForFlight() {
    string from, to;
    cout << "From >> ";
    cin >> from;
    cout << "To >> " << endl;
    cin >> to;
    from = stringToUpper(from);
    to = stringToUpper(to);

    int flightIndex = -1;
    for (int i = 0; i < flights.size(); ++i) {
        if (flights[i].getFrom() == from && flights[i].getTo() == to) {
            flightIndex = i;
            break;
        }
    }

    if (flightIndex == -1) {
        cout << "No flight was found!! Please try again..." << endl;
        PrintCrewsForFlight();
        return;
    }

    cout << "---- Crew List ----" << endl;
    int count = 0;
    for (auto crew : crews) {
        if (crew.getSchedule()[flightIndex] == '1') {
            count++;
            cout << crew.getName() << endl;
        }
    }

    if (count == 0) {
        cout << "No available crew for this flight." << endl;
    } else {
        cout << count << " crew(s) work(s) on the flight "
             << from << "-" << to << endl << endl;
    }
}

void CrewApp::PrintFlightsForCrew() {
    string memberName;
    cin >> memberName;
    memberName = stringToUpper(memberName);

    cout << "---- Assigned Flights ----" << endl;

    bool memberFound = false;
    for (auto member : crews) {
        if (member.getName() == memberName) {
            memberFound = true;
            string schedule = member.getSchedule();

            // Checking if they have a single flight booked
            int count = 0;
            for (int i = 0; i < schedule.length(); i++) {
                if (schedule.at(i) == '0') {
                    count++;
                }
            }
            if (schedule.length() == count) {
                cout << "No flight was assigned to " << memberName << endl <<  endl;
                return;
            }

            string firstFrom, currentFrom, currentTo, nextFrom, nextTo;
            bool feasible = true;
            int flightCount = 0;
            for (int i = 0; i < schedule.length(); i++) {
                if (schedule.at(i) == '1') {

                    if (flightCount < 1) {
                        firstFrom = flights[i].getFrom();
                    }
                    flightCount++;

                    currentFrom = flights[i].getFrom();
                    currentTo = flights[i].getTo();

                    for (int j = i + 1; j < schedule.length(); j++) {
                        if (schedule.at(j) == '1') {
                            nextFrom = flights[j].getFrom();
                            nextTo = flights[j].getTo();
                            break;
                        }
                        nextFrom = firstFrom;
                    }

                    cout << currentFrom << " - " << currentTo << endl;

                    if (currentTo != nextFrom && flightCount != 1) {
                        feasible = false;
                    }
                }
            }

            if (!feasible) {
                cout << "The flight sequence is NOT feasible" << endl;
            } else {
                cout << "The flight sequence is feasible" << endl;
            }
            break;
        }
    }
    if (!memberFound) {
        cout << "No record for " << memberName
             << ". Please try again..." << endl;
        PrintFlightsForCrew();
        return;
    }
}

void CrewApp::ExecuteMenu(int opt) {
    if (opt == 1) {
        PrintCrews();
        pressEnter();
    } else if (opt == 2) {
        PrintUniqueLocations();
        pressEnter();
    } else if (opt == 3) {
        PrintUniqueLocations();
        PrintCrewsForFlight();
        pressEnter();
    } else if (opt == 4) {
        cout << "Enter the crew name >> ";
        PrintFlightsForCrew();
        pressEnter();
    } else if (opt == -1) {
        cout << "Bye!" << endl;
    } else {
        cout << "The wrong choice!!!" << endl;
        pressEnter();
    }
}
