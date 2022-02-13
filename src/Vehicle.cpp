#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

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