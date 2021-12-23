//
// Created by antonio on 19. 12. 2021..
//

#include "View.h"
#include "TextureWithDestination.h"
#include <SDL_events.h>
#include <SDL.h>
#include <SDL_messagebox.h>

View::View(Controller &controller) : controller(controller) {
    window = nullptr;
    screenSurface = nullptr;
    pointerSurface = nullptr;
    rend = nullptr;
    tex = nullptr;
    dest = nullptr;
    dotRect = nullptr;
    dotSurface = nullptr;
    dotTexture = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow(
                "WaterPipes",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH + ADDITIONAL_WIDTH,
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
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
            pointerSurface = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/pointer.bmp");
            screenSurface = SDL_GetWindowSurface(window);
            tex = SDL_CreateTextureFromSurface(rend, pointerSurface);
            SDL_QueryTexture(tex, nullptr, nullptr, &dest->w, &dest->h);
            dest->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
            dest->w = SCREEN_WIDTH / LIMIT_RIGHT;

            dotRect = new SDL_Rect();
            dotRect->x = SCREEN_WIDTH + OFFSET_X_POINT;
            dotRect->y = OFFSET_Y;
            dotSurface = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/green_dot.bmp");
            dotTexture = SDL_CreateTextureFromSurface(rend, dotSurface);
            SDL_QueryTexture(dotTexture, nullptr, nullptr, &dotRect->w, &dotRect->h);
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
        SDL_RenderCopy(rend, dotTexture, nullptr, dotRect);
        for (TextureWithDestination textureDTO: pipesUiTextures)
            SDL_RenderCopy(rend, textureDTO.getTexture(), nullptr, textureDTO.getRect());

        for (TextureWithDestination textureDTO: poolTextures)
            SDL_RenderCopy(rend, textureDTO.getTexture(), nullptr, textureDTO.getRect());
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
                case changedPipe:
                    changePipeUI();
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
    newPool();
    printf("%d", controller.getPosition());
}

void View::showGameOver() {
    //TODO OpenGL
}

void View::placeFirstPipe() {
    Pipe pipe = Pipe(true);
    PositionedPipe firstPipe = PositionedPipe(LIMIT_RIGHT / 2, LIMIT_BOTTOM / 2, pipe);
    drawNewPipe(firstPipe.dimensionsInPx());
}

void View::changePipeUI() {
    int position = controller.getPosition();
    printf("%d", controller.getPosition());
    if (position != 0)
        dotRect->y += SCREEN_HEIGHT / 5;
    else
        dotRect->y = 25;

}

void View::newPool() {
    std::vector<Pipe> pool = controller.newPool();
    int counter = 0;
    poolTextures.clear();
    for (Pipe pipe: pool) {
        PipeUI pipeUi = PipeUI();
        PositionedPipe positioned = PositionedPipe(SCREEN_WIDTH + OFFSET_X_POOL,
                                                   OFFSET_Y + counter * SCREEN_HEIGHT / PIPE_POOL,
                                                   pipe);
        pipeUi.setDest(positioned.getPosition());
        pipeUi.setTypeFromPipe(positioned.getPipe());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, pipeUi.getSurface());
        TextureWithDestination newTexWithDest = TextureWithDestination(texture, pipeUi.getRect());
        poolTextures.push_back(newTexWithDest);
        SDL_QueryTexture(texture, nullptr, nullptr, &poolTextures.back().getRect()->w,
                         &poolTextures.back().getRect()->h);
        pipeUi.scale();
        counter++;
    }
}


