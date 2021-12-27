//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_VIEW_H
#define WPIPES_VIEW_H


#include <SDL_video.h>
#include <SDL_render.h>
#include <map>
#include "../contoller/Controller.h"
#include "PipeUI.h"
#include "TextureWithDestination.h"

class View {
    Controller controller;

    SDL_Window *window;
    SDL_Renderer *rend{};

    SDL_Texture *pointerTexture{};
    SDL_Rect *pointerRect{};

    SDL_Texture *dotTexture{};
    SDL_Rect *dotRect{};

    SDL_Texture *scoreTitleTexture{};
    SDL_Rect *scoreTitleRect{};

    SDL_Texture *freeEndsTitleTexture{};
    SDL_Rect *freeEndsTitleRect{};

    std::vector<TextureWithDestination> pipesUiTextures;
    std::vector<TextureWithDestination> poolTextures;

    std::vector<SDL_Texture *> scoreDigitTextures;
    std::vector<SDL_Rect *> scoreDigitRects;
    std::vector<TextureWithDestination> scoreDigits;

    std::vector<SDL_Texture *> freeEndTextures;
    std::vector<SDL_Rect *> freeEndRects;
    std::vector<TextureWithDestination> freeEndDigits;

    std::vector<SDL_Texture *> digitTextures;
    std::vector<SDL_Rect *> digitRects;
    std::vector<TextureWithDestination> timerDigits;

    std::map<std::string, SDL_Surface *> loadedBitmaps;

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

    void resultUi(int score);

    void freeEndsUi(int ends);

    void drawNewPipe(PositionedPipe pipe);

    void showGameOver();

    void placeFirstPipe();

    void changePipeUI();

    void newPool();

    void clockInit();

    void timeUi(const Time &time);

    void drawAllPipes();

    void drawPool();

    void drawTimer();

    void drawPointer();

    void drawPoolDot();

    void drawScoreTitle();

    void initBitmaps();

    void dotInit();

    void pointerInit();

    void initRenderer();

    void dummyInit();

    void scoreInit();

    void drawResult();

    void initFreeEnds();

    void drawRemaining();
};


#endif //WPIPES_VIEW_H
