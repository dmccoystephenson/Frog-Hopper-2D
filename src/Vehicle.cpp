#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "header/Vehicle.h"

Vehicle::Vehicle() {
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
}

void Vehicle::render(SDL_Renderer* gRenderer, SDL_Texture* carRightTexture, SDL_Texture* carLeftTexture, std::string direction) {
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

void Vehicle::move(const int SCREEN_WIDTH) {
	xpos += xvel;
	collider.x = xpos;
	
	// if too far left or right
	if ((xpos < -200) || (xpos + width > SCREEN_WIDTH + 200)) {
		// move to initial x
		xpos = initialX;
		collider.x = xpos;
	}
}