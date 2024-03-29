#ifndef Frog_h
#define Frog_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Frog {
  public:
	Frog();
	void render(SDL_Renderer* gRenderer, SDL_Texture* frogTexture);
	void init(int x, int y, int w, int h);
	void handleEvent(SDL_Event &e);
	void move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	int xpos;
	int ypos;
	int width;
	int height;
	int xvel;
	int yvel;
	SDL_Rect collider;
};

#endif