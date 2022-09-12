#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Vehicle {
  public:
	Vehicle();
	void render(SDL_Renderer* gRenderer, SDL_Texture* carRightTexture, SDL_Texture* carLeftTexture, std::string direction);
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