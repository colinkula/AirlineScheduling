/*
This program helps organize airline crew schedules. Users can check crew names,
see unique flight locations, and find crews for specific flights or flights for
particular crew members. It makes managing airline operations smoother by 
providing quick access to scheduling information.

Copyright by Colin Kula, 11/15/2023
*/

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
This function displays a message prompting the user to press enter to continue.
It is used to pause the program execution until the user presses the enter key.
*/
void pressEnter() {
    cout << "to continue, press enter..." << endl;
    cin.ignore();
    cin.get();
}

/*
This constructor sets the file names to empty strings and calls the ImportCrew,
ImportFlights, and FillUniqueFlights functions to populate the crews, flights,
and uniqueFLocations data members.
*/
CrewApp::CrewApp() {
    this->crewfileName = "";
    this->flightfileName = "";

    // Populate data members.
    ImportCrew();
    ImportFlights();
    FillUniqueFlights();
}

/*
This constructor takes crew and flight file names as parameters, sets them in
the instance, and then calls the same importing functions as the default
constructor.
*/
CrewApp::CrewApp(std::string crewfileName, std::string flightfileName) {
    this->crewfileName = crewfileName;
    this->flightfileName = flightfileName;

    // Populate data members.
    ImportCrew();
    ImportFlights();
    FillUniqueFlights();
}

/*
It opens the crew file and reads each line, parsing the name and schedule. A
Crew object is then created with this information and added to the crews
vector.
*/
void CrewApp::ImportCrew() {
    std::ifstream file(crewfileName);

    // Loop until the end of the file and make a Crew object for each line.
    // Push that Crew object to the crews vector.
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

/*
This function reads each line from the flight file, extracts the 'from' and
'to' information, creates a Flight object, and adds it to the flights vector.
*/
void CrewApp::ImportFlights() {
    std::ifstream file(flightfileName);

    // Loop until the end of the file and make a Crew object for each line.
    // Push that Crew object to the crews vector.
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

/*
This function iterates through the flights vector, checking for unique 'from'
and 'to' locations and adds them to the uniqueFLocations set.
*/
void CrewApp::FillUniqueFlights() {
    // Loop through all flights.
    for (int i = 0; i < flights.size(); i++) {
        // Add the 'from' location into the set if it is not already in the set.
        if (uniqueFLocations.count(flights[i].getFrom()) == 0) {
            uniqueFLocations.insert(flights[i].getFrom());
        }

        // Add the 'to' location into the set if it is not already in the set.
        if (uniqueFLocations.count(flights[i].getTo()) == 0) {
            uniqueFLocations.insert(flights[i].getTo());
        }
    }
}

/*
This function Prints the available menu options for the user to choose from.
*/
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

/*
This function outputs the names of all crew members in the crews vector.
*/
void CrewApp::PrintCrews() {
    cout << "---- Crew List ----" << endl;
    for (int i = 0; i < crews.size(); i++) {
        cout << crews[i].getName() << endl;
    }
    cout << endl;
}

/*
This function prints the unique 'from' and 'to' locations stored in the
uniqueFLocations set.
*/
void CrewApp::PrintUniqueLocations() {
    cout << "---- Flight Locations ----" << endl;
    for (const auto &element : uniqueFLocations) {
        cout << element << endl;
    }
    cout << endl;
}

/*
This function prompts the user for 'from' and 'to' locations, identifies the
corresponding flight, and prints the crew members available for that flight
based on their schedules.
*/
void CrewApp::PrintCrewsForFlight() {
    // Get input from the user and convert their inputs in to uppercase.
    string from, to;
    cout << "From >> ";
    cin >> from;
    cout << "To >> " << endl;
    cin >> to;
    from = stringToUpper(from);
    to = stringToUpper(to);

    // Loop all flights and check if the input 'from' and 'to' locations match
    // any of the flights. If they do match update the flight index and break
    // out of the loop.
    int flightIndex = -1;
    for (int i = 0; i < flights.size(); ++i) {
        if (flights[i].getFrom() == from && flights[i].getTo() == to) {
            flightIndex = i;
            break;
        }
    }

    // If a matching flight wasnt found in the previous loop, recursively call
    // the function again until a matching flight is found.
    if (flightIndex == -1) {
        cout << "No flight was found!! Please try again..." << endl;
        PrintCrewsForFlight();
        return;
    }

    // Loop through all crew members and check if their scheudle has a
    // corresponding 1 for the matching flight. If there is a 1 in the correct
    // bit (representing the flight index), print out that crew members name.
    cout << "---- Crew List ----" << endl;
    int count = 0;
    for (auto crew : crews) {
        if (crew.getSchedule()[flightIndex] == '1') {
            count++;
            cout << crew.getName() << endl;
        }
    }

    // A count variable was created to keep track of the number of crew members
    // for the matching flight. This prints out the correct output based on the
    // count.
    if (count == 0) {
        cout << "No available crew for this flight." << endl;
    } else {
        cout << count << " crew(s) work(s) on the flight "
             << from << "-" << to << endl << endl;
    }
}

/*
This function prompts the user for a crew name, identifies the corresponding
crew member, and prints the flights assigned to that crew, along with a
feasibility check for the flight sequence.
*/
void CrewApp::PrintFlightsForCrew() {
    // Get input from the user and convert their input to uppercase.
    string memberName;
    cin >> memberName;
    memberName = stringToUpper(memberName);
    cout << "---- Assigned Flights ----" << endl;

    // Loop through every Crew object from the crews vector and check if the
    // input member name matches any of the object's names.
    bool memberFound = false;
    for (auto member : crews) {
        if (member.getName() == memberName) {
            memberFound = true;
            string schedule = member.getSchedule();

            // Loop through the Crew object's schedule and count the number of
            // flights they are associated with.
            int count = 0;
            for (int i = 0; i < schedule.length(); i++) {
                if (schedule.at(i) == '0') {
                    count++;
                }
            }

            // Check if the Crew object does not have any scheduled flights.
            if (schedule.length() == count) {
                cout << "No flight was assigned to " << memberName
                     << endl <<  endl;
                return;
            }

            // Loop through the Crew object's schedule and check if the current
            // character is equal to 1.
            string firstFrom, currentFrom, currentTo, nextFrom, nextTo;
            bool feasible = true;
            int flightCount = 0;
            for (int i = 0; i < schedule.length(); i++) {
                if (schedule.at(i) == '1') {
                    // The first instance of a flight stores the firstFrom
                    // variable. This helps when checking for feasibility
                    // after all of the Crew object's schedule is looped
                    // through. flightCount is incrememented to ensure that
                    // only the first instance is recorded.
                    if (flightCount < 1) {
                        firstFrom = flights[i].getFrom();
                    }
                    flightCount++;

                    // Assign the current 'from' and 'to' locations in the
                    // associated variables.
                    currentFrom = flights[i].getFrom();
                    currentTo = flights[i].getTo();

                    // Loop through the Crew object's schedule starting at the
                    // previous loop's current index and find the next instance
                    // of a scheduled flight. If found, the next 'from' and
                    // 'to' locations are stored in the associated variables
                    // and the loop is broken out of. If a scheduled flight is
                    // not found, the nextFrom variable is set to firstFrom.
                    // This ensures the correct check for feasibility because
                    // in order for a flight sequence to be feasibile, the
                    // starting location and the ending location have to be
                    // the same.
                    for (int j = i + 1; j < schedule.length(); j++) {
                        if (schedule.at(j) == '1') {
                            nextFrom = flights[j].getFrom();
                            nextTo = flights[j].getTo();
                            break;
                        }
                        nextFrom = firstFrom;
                    }

                    // Prinitng out the current 'from' and 'to' locations.
                    cout << currentFrom << " - " << currentTo << endl;

                    // This checks if the current 'to' and next 'from'
                    // locations match. If they do not match, the flight path
                    // is no longer feasible. Simultaneously, flightCount must
                    // be checked because if flightCount is equal to 1, then
                    // the flight sequence is feasible.
                    if (currentTo != nextFrom && flightCount != 1) {
                        feasible = false;
                    }
                }
            }

            // Prints out the correct feasibility statement.
            if (!feasible) {
                cout << "The flight sequence is NOT feasible" << endl;
            } else {
                cout << "The flight sequence is feasible" << endl;
            }
            break;
        }
    }

    // If the input members name does not correspond to any of the Crew
    // object's names, then the function is recursively called until the user
    // inputs a correct name.
    if (!memberFound) {
        cout << "No record for " << memberName
             << ". Please try again..." << endl;
        PrintFlightsForCrew();
        return;
    }
}

/*
This function takes the user's menu choice as a parameter and calls the
appropriate function based on the choice. It also handles invalid choices and
displays corresponding messages.
*/
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
