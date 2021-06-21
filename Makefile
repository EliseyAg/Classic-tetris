CXX=g++
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system  -lsfml-audio
SOURCES=main.cpp Game.cpp Sprite.cpp Menu.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tetris
OS=$(shell uname)
LINUX=$(OS)
CXXFLAGS=-c -Wall -DLINUX -I/usr/include/SFML

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
