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

// box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

void renderScene();

void gameScreen();

void loseScreen();

void winScreen();

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


class Vehicle {
  public:
	Vehicle();
	void render(string direction);
	void init(int x, int y, int w, int h, int xspeed, int xinitial);
	void move();
	int xpos;
	int ypos;
	int width;
	int height;
	int xvel;
	int initialX;
	SDL_Rect collider;
	
};

// textures
SDL_Texture* background;
SDL_Texture* frogTexture;
SDL_Texture* carRightTexture;
SDL_Texture* carLeftTexture;
SDL_Texture* loseTexture;
SDL_Texture* winTexture;

// objects
Frog frog;
Vehicle bottomCarRight;
Vehicle topCarRight;
Vehicle bottomCarLeft;
Vehicle topCarLeft;

int frogX = 475;
int frogY = 675;
int frogW = 75;
int frogH = 75;

int frogSpeed = 4;

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Frog Hopper - Frogger Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void loadMedia() {
	SDL_Surface* temp_surface;
	temp_surface = IMG_Load("background.png");
	background = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("frog.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	frogTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("carRight.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	carRightTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("carLeft.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	carLeftTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("playerLose.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	loseTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	temp_surface = IMG_Load("playerWin.png");
	SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0, 0xFF, 0xFF));
	winTexture = SDL_CreateTextureFromSurface(gRenderer, temp_surface);
	SDL_FreeSurface(temp_surface);
}

void cleanUp() {
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
bool checkCollision(SDL_Rect a, SDL_Rect b) {
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
	
	// if collided with a car
	if (checkCollision(collider, bottomCarLeft.collider) ||
		checkCollision(collider, topCarLeft.collider) ||
		checkCollision(collider, bottomCarRight.collider) ||
		checkCollision(collider, topCarRight.collider)) {
			xvel = 0;
			yvel = 0;
			loseScreen();
		}
	
	ypos += yvel;
	collider.y = ypos;
	
	// if too far up or down
	if ((ypos < -100) || (ypos + height > SCREEN_HEIGHT)) {
		// move back
		ypos -= yvel;
		collider.y = ypos;
	}
}

Vehicle::Vehicle() {
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
}

void Vehicle::render(string direction) {
	SDL_Rect renderQuad = {xpos, ypos, width, height};
	if (direction == "right") {
		SDL_RenderCopy(gRenderer, carRightTexture, NULL, &renderQuad);
	}
	else if (direction == "left") {
		SDL_RenderCopy(gRenderer, carLeftTexture, NULL, &renderQuad);
	}
}

void Vehicle::init(int x, int y, int w, int h, int xspeed, int xinitial) {
	xpos = x;
	ypos = y;
	width = w;
	height = h;
	collider = {x, y, w, h};
	xvel = xspeed;
	initialX = xinitial;
}

void Vehicle::move() {
	xpos += xvel;
	collider.x = xpos;
	
	// if too far left or right
	if ((xpos < -200) || (xpos + width > SCREEN_WIDTH + 200)) {
		// move to initial x
		xpos = initialX;
		collider.x = xpos;
	}
}

void renderScene() {	
	SDL_RenderCopy(gRenderer, background, NULL, NULL);
	frog.render();
	bottomCarRight.render("right");
	topCarRight.render("right");
	bottomCarLeft.render("left");
	topCarLeft.render("left");
}

bool checkWin() {
	if (frog.ypos < -75) {
		winScreen();
	}
}

void gameScreen() {
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
		frog.move();
		bottomCarRight.move();
		topCarRight.move();
		bottomCarLeft.move();
		topCarLeft.move();
		checkWin();
		SDL_RenderPresent(gRenderer);
	}
}

void loseScreen() {
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

void winScreen() {
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
	init();
	loadMedia();
	gameScreen();
	cleanUp();
	return 0;
}