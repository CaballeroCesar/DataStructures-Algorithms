CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
wordscanner: wordscanner.o
	$(CXX) $(CXXFLAGS) -o $@ $^

wordscanner.o: wordscanner.cc 
	$(CXX) $(CXXFLAGS) -c -o $@ $<