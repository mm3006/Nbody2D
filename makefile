
CXX = g++
CXXFLAGS = -Wall -g -O3 -std=c++14 

TARGET = main

TARGET_DEL = main.o
SRCS = main.cpp Moon.cpp Planet.cpp Star.cpp System.cpp CelestialObject.cpp


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