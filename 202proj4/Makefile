CXX = g++
CXXFLAGS = -Wall -g

proj4: Game.o Area.o Hydralisk.o Mutalisk.o Zergling.o Battlecruiser.o Ghost.o Marine.o Zerg.o Terran.o Entity.o proj4.cpp
	$(CXX) $(CXXFLAGS) Game.o Area.o Hydralisk.o Mutalisk.o Zergling.o Battlecruiser.o Ghost.o Marine.o Zerg.o Terran.o Entity.o proj4.cpp -o proj4

Entity.o: Entity.h Entity.cpp
	$(CXX) $(CXXFLAGS) -c Entity.cpp

Terran.o: Terran.h Terran.cpp Entity.o
	$(CXX) $(CXXFLAGS) -c Terran.cpp

Zerg.o: Zerg.h Zerg.cpp Entity.o
	$(CXX) $(CXXFLAGS) -c Zerg.cpp

Marine.o: Marine.h Marine.cpp Terran.o Entity.o
	$(CXX) $(CXXFLAGS) -c Marine.cpp

Ghost.o: Ghost.h Ghost.cpp Terran.o Entity.o
	$(CXX) $(CXXFLAGS) -c Ghost.cpp

Battlecruiser.o: Battlecruiser.h Battlecruiser.cpp Terran.o Entity.o
	$(CXX) $(CXXFLAGS) -c Battlecruiser.cpp

Zergling.o: Zergling.h Zergling.cpp Zerg.o Entity.o
	$(CXX) $(CXXFLAGS) -c Zergling.cpp

Mutalisk.o: Mutalisk.h Mutalisk.cpp Zerg.o Entity.o
	$(CXX) $(CXXFLAGS) -c Mutalisk.cpp

Hydralisk.o: Hydralisk.h Hydralisk.cpp Zerg.o Entity.o
	$(CXX) $(CXXFLAGS) -c Hydralisk.cpp

Area.o: Area.h Area.cpp
	$(CXX) $(CXXFLAGS) -c Area.cpp

Game.o: Game.cpp Game.h Area.o Hydralisk.o Mutalisk.o Zergling.o Battlecruiser.o Ghost.o Marine.o Zerg.o Terran.o Entity.o
	$(CXX) $(CXXFLAGS) -c Game.cpp

run:
	./proj4

run1:
	./proj4 proj4_map1.txt

val1:
	valgrind ./proj4 proj4_map1.txt