FG_FILES = src/Frog.cpp src/FrogHopper.cpp src/Vehicle.cpp

all: frogHopper

frogHopper: src/frogHopper.cpp
	g++ src/frogHopper.cpp $(FG_FILES) -o frogHopper_executable