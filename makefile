
CXX = g++
CXXFLAGS = -Wall -g -O2 -std=c++14

TARGET = main

TARGET_DEL = main.o
SRCS = main.cpp CelestialBody.cpp Moon.cpp Planet.cpp Star.cpp Utils.cpp System.cpp


OBJS = $(SRCS:.cpp=.o)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

all: $(TARGET) run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	rm -f $(TARGET_DEL) $(OBJS)