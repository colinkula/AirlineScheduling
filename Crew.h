/*
The Crew class manages airline crew members' names and schedules. It includes
constructors for easy initialization and provides methods to set and retrieve
this information. The class is designed for use in an airline scheduling
application.

Copyright by Colin Kula, 11/15/2023
*/

#ifndef CREW_H
#define CREW_H
#include<string>
class Crew {
 private:
        std::string name;
        std::string schedule;
 public:
        Crew();
        Crew(std::string name, std::string schedule);
        void setName(std::string name);
        void setSchedule(std::string schedule);
        std::string getName();
        std::string getSchedule();
};
#endif  // CREW_H
