app : main.o Crew.o Flight.o CrewApp.o
	g++ main.o Crew.o Flight.o CrewApp.o -o app
main.o : main.cpp
	g++ -c main.cpp -o main.o
Crew.o : Crew.cpp
	g++ -c Crew.cpp -o Crew.o
Flight.o : Flight.cpp
	g++ -c Flight.cpp -o Flight.o
CrewApp.o : CrewApp.cpp
	g++ -c CrewApp.cpp -o CrewApp.o
runapp :
	./app CrewSchedule.txt Flights.txt
clean :
	rm *.o
	rm app
