FG_FILES = src/Frog.cpp src/FrogHopper.cpp src/Vehicle.cpp

all: frogHopper

frogHopper: src/frogHopper.cpp
	g++ src/frogHopper.cpp $(FG_FILES) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o frogHopper_executable