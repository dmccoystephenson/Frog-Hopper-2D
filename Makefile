
all: frogHopper

frogHopper: frogHopper.cpp
	@echo "---"
	@echo "Compiling frogHopper.cpp"

	g++ frogHopper.cpp -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o frogHopper

	@echo "Finished compiling frogHopper.cpp"