CXX=g++
CXXFLAGS= -c -Wall -Wextra -pedantic-errors -std=c++0x -g
RM=rm -f

play: Lift.o Space.o Food.o Game.o inputValidation.o main.o Menu.o Item.o DerivedSpaces.o
	$(CXX) -g Lift.o Space.o Food.o Game.o inputValidation.o main.o Item.o Menu.o DerivedSpaces.o -o play

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

Game.o: Game.cpp Game.hpp
	$(CXX) $(CXXFLAGS) Game.cpp
	
Item.o: Item.cpp Item.hpp
	$(CXX) $(CXXFLAGS) Item.cpp

Food.o: Food.cpp Food.hpp
	$(CXX) $(CXXFLAGS) Food.cpp

Lift.o: Lift.cpp Lift.hpp
	$(CXX) $(CXXFLAGS) Lift.cpp

Menu.o: Menu.cpp Menu.hpp
	$(CXX) $(CXXFLAGS) Menu.cpp
	
DerivedSpaces.o: DerivedSpaces.cpp DerivedSpaces.hpp
	$(CXX) $(CXXFLAGS) DerivedSpaces.cpp

inputValidation.o: inputValidation.cpp inputValidation.hpp
	$(CXX) $(CXXFLAGS) inputValidation.cpp
	
Space.o: Space.cpp Space.hpp
	$(CXX) $(CXXFLAGS) Space.cpp

clean:
	$(RM) *.o play *~ 
