#ifndef FrogHopper_h
#define FrogHopper_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Frog.h"
#include "Vehicle.h"

class FrogHopper {
    public:
        FrogHopper();
        void loadMedia();
        void cleanUp();
        bool checkCollision(SDL_Rect a, SDL_Rect b);
        void renderScene();
        void gameScreen();
        void loseScreen();
        void winScreen();
        bool checkWin();

        SDL_Window* gWindow = NULL;
        SDL_Renderer* gRenderer = NULL;

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

        const int SCREEN_WIDTH = 1000;
        const int SCREEN_HEIGHT = 750;
};

#endif