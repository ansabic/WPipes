//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_VIEW_H
#define WPIPES_VIEW_H


#include <SDL_video.h>
#include <SDL_render.h>
#include "../contoller/Controller.h"

class View {
    Controller controller;
    SDL_Window *window;
    SDL_Surface *screenSurface;
    SDL_Surface *pointerSurface;
    SDL_Renderer *rend;
    SDL_Texture *tex;
    SDL_Rect *dest;

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

};


#endif //WPIPES_VIEW_H
