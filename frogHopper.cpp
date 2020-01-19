#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

void init();

void loadMedia();

void cleanUp();

// textures
SDL_Texture* background;
SDL_Texture* frogTexture;

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Frog Hopper - Frogger Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	//  initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
}

void loadMedia() {
	SDL_Surface* temp_surface;
	temp_surface = IMG_Load("background.png");
	background = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("frog.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	frogTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	SDL_FreeSurface(temp_surface);
}

void cleanUp() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}
/*
class Vehicle {
  public:
	
  private:
	
}
*/
/*
class Frog {
  public:
	Frog();
	void render();
  private:
	
}
*/
void renderScene() {
	SDL_RenderCopy(gRenderer, background, NULL, NULL);
	SDL_Rect renderQuad = { 475, 675, 75, 75};
	SDL_RenderCopy(gRenderer, frogTexture, NULL, &renderQuad);
}

void frogger() {
	renderScene();
//	Frog.render();
}

int main(int argc, char* args[]) {
	init();
	loadMedia();
	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}
		SDL_RenderClear(gRenderer);
		frogger();
		SDL_RenderPresent(gRenderer);
	}
	cleanUp();
	return 0;
}