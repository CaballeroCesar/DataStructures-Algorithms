CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
parking: parking.o car.o garage.o
	$(CXX) $(CXXFLAGS) -o $@ $^

parking.o: parking.cc 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

car.o: car.cc car.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

garage.o: garage.cc garage.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<