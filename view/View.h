//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_VIEW_H
#define WPIPES_VIEW_H


#include <SDL_video.h>
#include <SDL_render.h>
#include "../contoller/Controller.h"
#include "PipeUI.h"
#include "TextureWithDestination.h"

class View {
    Controller controller;
    SDL_Window *window;
    SDL_Surface *screenSurface;
    SDL_Surface *pointerSurface;
    SDL_Renderer *rend;
    SDL_Texture *tex;
    SDL_Rect *dest;
    SDL_Surface *dotSurface;
    SDL_Texture *dotTexture;
    SDL_Rect *dotRect;
    std::vector<TextureWithDestination> pipesUiTextures;
    std::vector<TextureWithDestination> poolTextures;

    void listenForEvents();

public:
    explicit View(Controller &controller);

    void loop();

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

    void spawnNew();

    void movementError();

    void placementError();

    void showResult(int score);

    void showFreeEnds(int ends);

    void drawNewPipe(PositionedPipe pipe);

    void showGameOver();

    void placeFirstPipe();

    void changePipe();

    void listenForChanges();
};


#endif //WPIPES_VIEW_H
