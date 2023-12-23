#include <iostream>
// Purpose

// Coding Trails:
// Attempt #1 - I implemented a check for the correct number of arguments and a
//              check for correct file in the main function. I also completed
//              the crew.cpp and flight.cpp files, and began parts of the
//              CrewApp.cpp file. I had an error because I neglected to add
//              the command line arguments into my makefile.

// Attempt #2 - After I was succesfully able to test my program using zybook,
//              I fixed all errors and got the first 4 tests to work.

// Attempt #3 - I implemented multiple methods in CrewApp.cpp. I did not
//              imlement options 2-4, but option 1 is working besides a simple
//              formatting error.

// Attempt #4 - I implemented the PrintCrews function and PrintUniqeLocations
//              and had trouble with formatting because everytime I submitted,
//              a different formatting error would reveal itself.

// Attempt #5 - I implemented the PrintCrewForFLights method and had trouble
//              with the logic in the function. Specifically, I set my flight
//              index to 0 when it needed to be -1. I also had trouble with
//              formatting becasue it would print the flights after choosing
//              two incorrect flights when it wasnt supposed to.

// Attempt #6 - I implemented the PrintFlightsForCrew function after trying
//              to get it to work in vs code. I had lots of errors related to
//              the feasibility checks, and in the process made the code messy.
//              I fixed most errors but am stuck in a loop for test 16 because
//              it takes in incorrect inputs for a majority of the functiouns
//              in the program.

// Attempt #7 - After putting in checks for all user inputs, zybook revealed
//              that option 4 is supposed to loop until the user gets a correct
//              input. So I ade the function recursive and fixed other f
//              ormatting errors to get 76/100.
#include <fstream>
#include <string>
#include "./CrewApp.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Error!!! Incorrect program arguments" << endl
             << "Format : applicationName [filenameForCrew] [filenameForFlight]"
             << endl;
        return 1;
    }

    std::ifstream crewsFile(argv[1]);
    std::ifstream flightsFile(argv[2]);

    if (!crewsFile.is_open()) {
        cout << "The filename given for crews was not found!!!" << endl
             << "Program ends with an error." << endl;
        return 1;
    } else if (!flightsFile.is_open()) {
        cout << "The filename given for flights was not found!!!" << endl
             << "Program ends with an error." << endl;
        return 1;
    }

    CrewApp app(argv[1], argv[2]);

    int choice;
    do {
        app.PrintMenu();

        cout << "Enter your choice >> ";

        if (!(cin >> choice)) {
            cin.clear();
            choice = -999;
        }
        app.ExecuteMenu(choice);
    } while (choice != -1);

    return 0;
}
