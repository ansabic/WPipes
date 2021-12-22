//
// Created by antonio on 19. 12. 2021..
//

#include "View.h"
#include "../common/Constants.h"
#include "TextureWithDestination.h"
#include <SDL_events.h>
#include <SDL.h>

View::View(Controller &controller) : controller(controller) {
    window = nullptr;
    screenSurface = nullptr;
    pointerSurface = nullptr;
    rend = nullptr;
    tex = nullptr;
    dest = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow(
                "WaterPipes",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                0);
        if (window == nullptr)
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        else {
            dest = new SDL_Rect();
            dest->x = 0;
            dest->y = 0;
            Uint32 render_flags = SDL_RENDERER_ACCELERATED;
            rend = SDL_CreateRenderer(window, -1, render_flags);
            pointerSurface = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/pointer.bmp");
            screenSurface = SDL_GetWindowSurface(window);
            tex = SDL_CreateTextureFromSurface(rend, pointerSurface);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_QueryTexture(tex, nullptr, nullptr, &dest->w, &dest->h);
            dest->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
            dest->w = SCREEN_WIDTH / LIMIT_RIGHT;
        }
    }
}

void View::loop() {
    controller.begin();
    placeFirstPipe();
    while (controller.isPlaying()) {
        listenForEvents();

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, nullptr, dest);
        for (TextureWithDestination textureDTO: pipesUiTextures) {
            SDL_RenderCopy(rend, textureDTO.getTexture(), nullptr, textureDTO.getRect());
        }
        SDL_RenderPresent(rend);

        SDL_Delay(1000 / FPS);
    }
}

void View::listenForEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            Action result = controller.checkState(event.key.keysym.scancode);
            switch (result) {
                case movedUp:
                    moveUp();
                    break;
                case movedDown:
                    moveDown();
                    break;
                case movedLeft:
                    moveLeft();
                    break;
                case movedRight:
                    moveRight();
                    break;
                case hitEnterOrSpace:
                    spawnNew();
                    break;
                case showErrorMovement:
                    movementError();
                    break;
                case showErrorPlacement:
                    placementError();
                    break;
                case gameEndedFull:
                    showGameOver();
                    break;
                case neutral:
                    break;
            }
        }
    }

}

void View::spawnNew() {
    GameStateDTO state = controller.getState();
    showResult(state.score);
    showFreeEnds(state.freeEnds);
    drawNewPipe(state.newPipe.dimensionsInPx());
}

void View::moveUp() {
    dest->y -= SCREEN_HEIGHT / LIMIT_BOTTOM;
}

void View::moveDown() {
    dest->y += SCREEN_HEIGHT / LIMIT_BOTTOM;
}

void View::moveLeft() {
    dest->x -= SCREEN_WIDTH / LIMIT_RIGHT;
}

void View::moveRight() {
    dest->x += SCREEN_WIDTH / LIMIT_RIGHT;
}

void View::movementError() {
    //TODO OpenGL
}

void View::placementError() {
    //TODO OpenGL
}

void View::showResult(int score) {
    //TODO OpenGL
}

void View::showFreeEnds(int ends) {
    //TODO OpenGL
}

void View::drawNewPipe(PositionedPipe pipe) {
    PipeUI pipeUi = PipeUI();
    pipeUi.setDest(pipe.getPosition());
    pipeUi.setTypeFromPipe(pipe.getPipe());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, pipeUi.getSurface());
    TextureWithDestination newTexWithDest = TextureWithDestination(texture, pipeUi.getRect());
    pipesUiTextures.push_back(newTexWithDest);
    SDL_QueryTexture(texture, nullptr, nullptr, &pipeUi.getRect()->w, &pipeUi.getRect()->h);
    pipeUi.scale();
}

void View::showGameOver() {
    //TODO OpenGL
}

void View::placeFirstPipe() {
    PositionedPipe firstPipe = controller.placeFirstPipe();
    drawNewPipe(firstPipe.dimensionsInPx());
}


