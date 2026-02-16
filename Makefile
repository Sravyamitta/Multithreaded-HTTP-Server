CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread -Iinclude
TARGET = server
SRC = main.cpp src/Server.cpp src/ThreadPool.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
