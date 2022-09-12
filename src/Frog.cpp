#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "header/Frog.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;

Frog::Frog() {
	xpos = 0;
	ypos = 0;
	width = 0;
	height = 0;
	xvel = 0;
	yvel = 0;
}

void Frog::render(SDL_Renderer* gRenderer, SDL_Texture* frogTexture) {
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
	if ((ypos < -100) || (ypos + height > SCREEN_HEIGHT)) {
		// move back
		ypos -= yvel;
		collider.y = ypos;
	}
}