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

void renderScene();

void start();

class Frog {
  public:
	Frog();
	void render();
	void init(int x, int y, int w, int h);
	void handleEvent(SDL_Event &e);
	void move();
	int xpos;
	int ypos;
	int width;
	int height;
	int xvel;
	int yvel;
	SDL_Rect collider;
};

// textures
SDL_Texture* background;
SDL_Texture* frogTexture;

// objects
Frog frog;

int frogX = 475;
int frogY = 675;
int frogW = 75;
int frogH = 75;

int frogSpeed = 4;

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Frog Hopper - Frogger Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	// initialize and render frog
	frog.init(frogX, frogY, frogW, frogH);	
	
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

Frog::Frog() {
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
	xvel = 0;
	yvel = 0;
}

void Frog::render() {
	SDL_Rect renderQuad = {xpos, ypos, width, height};
	SDL_RenderCopy(gRenderer, frogTexture, NULL, &renderQuad);
}

void Frog::init(int x, int y, int w, int h) {
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	collider = {x, y, w, h};
}

void Frog::handleEvent(SDL_Event &e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				yvel -= 4;
				break;
			case SDLK_DOWN:
				yvel += 4;
				break;
			case SDLK_LEFT:
				xvel -= 4;
				break;
			case SDLK_RIGHT:
				xvel += 4;
				break;
		}
	}
	
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				yvel += 4;
				break;
			case SDLK_DOWN:
				yvel -= 4;
				break;
			case SDLK_LEFT:
				xvel += 4;
				break;
			case SDLK_RIGHT:
				xvel -= 4;
				break;
		}
	}
}

void Frog::move() {
	xpos += xvel;
	collider.x = xpos;
	
	// if too far left or right
	if ((xpos < 0) || (xpos + width > SCREEN_WIDTH)) {
		// move back
		xpos -= xvel;
		collider.x = xpos;
	}
	
	ypos += yvel;
	collider.y = ypos;
	
	// if too far up or down
	if ((ypos < 0) || (ypos + height > SCREEN_HEIGHT)) {
		// move back
		ypos -= yvel;
		collider.y = ypos;
	}
}

void renderScene() {	
	SDL_RenderCopy(gRenderer, background, NULL, NULL);
	frog.render();
}

bool checkWin() {
	if (frog.ypos < 15) {
		SDL_Delay(500);
		frog.ypos = 675;
	}
}

void start() {
	renderScene();
	frog.move();
	checkWin();
	frog.render();
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
			frog.handleEvent(e);
		}
		SDL_RenderClear(gRenderer);
		start();
		SDL_RenderPresent(gRenderer);
	}
	cleanUp();
	return 0;
}