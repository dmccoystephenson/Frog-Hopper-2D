#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "header/FrogHopper.h"
#include "header/Frog.h"
#include "header/Vehicle.h"

FrogHopper::FrogHopper() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Frog Hopper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// initialize objects
	frog.init(frogX, frogY, frogW, frogH);	
	bottomCarRight.init(-200, 550, 200, 100, 6, -200);
	topCarRight.init(500, 200, 200, 100, 7, -200);
	bottomCarLeft.init(400, 450, 200, 100, -8, SCREEN_WIDTH);
	topCarLeft.init(200, 100, 200, 100, -9, SCREEN_WIDTH);
	
	//  initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
}

void FrogHopper::loadMedia() {
	SDL_Surface* temp_surface;
	temp_surface = IMG_Load("../resources/background.png");
	background = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("../resources/frog.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	frogTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("../resources/carRight.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	carRightTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("../resources/carLeft.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	carLeftTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("../resources/playerLose.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	loseTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("../resources/playerWin.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	winTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	SDL_FreeSurface(temp_surface);
}

void FrogHopper::cleanUp() {
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(frogTexture);
	SDL_DestroyTexture(carRightTexture);
	SDL_DestroyTexture(carLeftTexture);
	SDL_DestroyTexture(loseTexture);
	SDL_DestroyTexture(winTexture);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

// box collision detector
bool FrogHopper::checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA = a.x;
	int rightA = a.x + a.w;
	int topA = a.y;
	int bottomA = a.y + a.h;
	int leftB = b.x;
	int rightB = b.x + b.w;
	int topB = b.y;
	int bottomB = b.y + b.h;
	
	// check if boxes are not touching
	if (leftA >= rightB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (bottomA <= topB) {
		return false;
	}
	
	// otherwise
	return true;
}

void FrogHopper::renderScene() {	
	SDL_RenderCopy(gRenderer, background, NULL, NULL);
	frog.render(gRenderer, frogTexture);
	bottomCarRight.render(gRenderer, carRightTexture, carLeftTexture, "right");
	topCarRight.render(gRenderer, carRightTexture, carLeftTexture, "right");
	bottomCarLeft.render(gRenderer, carRightTexture, carLeftTexture, "left");
	topCarLeft.render(gRenderer, carRightTexture, carLeftTexture, "left");
}

bool FrogHopper::checkWin() {
	if (frog.ypos < -75) {
		winScreen();
		return true;
	}
	return false;
}

void FrogHopper::gameScreen() {
	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			frog.handleEvent(e);
		}
		SDL_RenderClear(gRenderer);
		renderScene();
		frog.move(SCREEN_WIDTH, SCREEN_HEIGHT);

	// if collided with a car
	if (checkCollision(frog.collider, bottomCarLeft.collider) ||
		checkCollision(frog.collider, topCarLeft.collider) ||
		checkCollision(frog.collider, bottomCarRight.collider) ||
		checkCollision(frog.collider, topCarRight.collider)) {
			frog.xvel = 0;
			frog.yvel = 0;
			loseScreen();
		}

		bottomCarRight.move(SCREEN_WIDTH);
		topCarRight.move(SCREEN_WIDTH);
		bottomCarLeft.move(SCREEN_WIDTH);
		topCarLeft.move(SCREEN_WIDTH);
		
		checkWin();
		SDL_RenderPresent(gRenderer);
	}
}

void FrogHopper::loseScreen() {
	frog.ypos = 675;
	bool showing = true;
	SDL_Event e;
	while (showing) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				cleanUp();
			}
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				cleanUp();
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, loseTexture, NULL, NULL);
		SDL_RenderPresent(gRenderer);
	}
}

void FrogHopper::winScreen() {
	frog.ypos = 675;
	bool showing = true;
	SDL_Event ev;
	while (showing) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				cleanUp();
			}
			if (ev.type == SDL_KEYDOWN && ev.key.repeat == 0) {
				cleanUp();
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, winTexture, NULL, NULL);
		SDL_RenderPresent(gRenderer);
	}
}

int main(int argc, char* args[]) {
	FrogHopper frogHopper;
	frogHopper.loadMedia();
	frogHopper.gameScreen();
	frogHopper.cleanUp();
	return 0;
}