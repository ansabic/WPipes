//
// Created by antonio on 19. 12. 2021..
//

#include "View.h"
#include "TextureWithDestination.h"
#include <SDL_events.h>
#include <SDL.h>
#include <SDL_messagebox.h>

View::View(Controller &controller) : controller(controller) {
    dummyInit();

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
            initRenderer();
            initBitmaps();
            pointerInit();
            dotInit();
            clockInit();
            scoreInit();
            initFreeEnds();
            goalsInit();
        }
    }
}

void View::loop() {
    controller.begin();
    placeFirstPipe();
    while (!controller.isGameOver()) {
        Time currentTime = controller.timeFlies();
        if (currentTime.isDone())
            controller.timeOut();
        timeUi(currentTime);
        if (controller.isPlaying())
            listenForEvents();
        else {
            controller.setGameOver(true);
            showGameOver();
        }

        SDL_RenderClear(rend);

        drawPointer();
        drawGoalPositions();
        drawPoolDot();
        drawAllPipes();
        drawPool();
        drawTimer();
        drawTowDots();
        drawScoreTitle();
        drawResult();
        drawRemaining();

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
                    controller.rewardTime();
                    spawnNew();
                    break;
                case showErrorMovement:
                    controller.timePenalty();
                    movementError();
                    break;
                case showErrorPlacement:
                    controller.timePenalty();
                    placementError();
                    break;
                case gameEnded:
                    controller.setGameOver(true);
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
    resultUi(state.score);
    freeEndsUi(state.freeEnds);
    drawNewPipe(state.newPipe.dimensionsInPx());
}

void View::moveUp() {
    pointerRect->y -= SCREEN_HEIGHT / LIMIT_BOTTOM;
}

void View::moveDown() {
    pointerRect->y += SCREEN_HEIGHT / LIMIT_BOTTOM;
}

void View::moveLeft() {
    pointerRect->x -= SCREEN_WIDTH / LIMIT_RIGHT;
}

void View::moveRight() {
    pointerRect->x += SCREEN_WIDTH / LIMIT_RIGHT;
}

void View::movementError() {
    int flag = SDL_MESSAGEBOX_INFORMATION;
    SDL_ShowSimpleMessageBox(flag, "Movement Error", "Movement not allowed! Out of bounds!", window);
}

void View::placementError() {
    int flag = SDL_MESSAGEBOX_INFORMATION;
    SDL_ShowSimpleMessageBox(flag, "Placement Error",
                             "Error placing pipe! Already exists there or not connected properly!", window);
}

void View::showGameOver() {
    int flag = SDL_MESSAGEBOX_INFORMATION;
    int multiplier = 1;
    if (controller.getState().solvedStart)
        multiplier++;
    if (controller.getState().solvedEnd)
        multiplier++;
    std::string score = std::to_string(controller.getState().score * multiplier / controller.getState().freeEnds);
    std::string firstString = "Game over! Your Score is ";
    std::string resultString = firstString.append(score);
    SDL_ShowSimpleMessageBox(flag, "GAME OVER", resultString.c_str(), window);
}

void View::resultUi(int score) {
    Number scoreNumb = Number(score);
    int counter = 0;
    for (int i = MAX_DIGITS - scoreNumb.getSize(); i < MAX_DIGITS; i++) {
        SDL_Rect *scoreDigit = scoreDigitRects[i];
        int digitNumber = scoreNumb.getDigit(counter);
        SDL_DestroyTexture(scoreDigitTextures[i]);
        scoreDigitTextures[i] = SDL_CreateTextureFromSurface(rend, loadedBitmaps[std::to_string(digitNumber)]);
        SDL_Texture *digitTexture = scoreDigitTextures[i];
        scoreDigits[i] = TextureWithDestination(digitTexture, scoreDigit);
        counter++;
    }
}

void View::freeEndsUi(int ends) {
    Number freeEndsNumb = Number(ends);
    int counter = 0;
    for (int i = MAX_DIGITS - freeEndsNumb.getSize(); i < MAX_DIGITS; i++) {
        SDL_Rect *freeEndsDigit = freeEndRects[i];
        int digitNumber = freeEndsNumb.getDigit(counter);
        SDL_DestroyTexture(freeEndTextures[i]);
        freeEndTextures[i] = SDL_CreateTextureFromSurface(rend, loadedBitmaps[std::to_string(digitNumber)]);
        SDL_Texture *digitTexture = freeEndTextures[i];
        freeEndDigits[i] = TextureWithDestination(digitTexture, freeEndsDigit);
        counter++;
    }
}

void View::drawNewPipe(PositionedPipe pipe) {
    PipeUI pipeUi = PipeUI();
    pipeUi.setDest(pipe.getPosition());
    pipeUi.setTypeFromPipe(pipe.getPipe());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, loadedBitmaps[pipeUi.getType()]);
    TextureWithDestination newTexWithDest = TextureWithDestination(texture, pipeUi.getRect());
    pipesUiTextures.push_back(newTexWithDest);
    SDL_QueryTexture(texture, nullptr, nullptr, &pipeUi.getRect()->w, &pipeUi.getRect()->h);
    pipeUi.scale();
    newPool();
}

void View::placeFirstPipe() {
    Pipe pipe = Pipe(true);
    PositionedPipe firstPipe = PositionedPipe(LIMIT_RIGHT / 2, LIMIT_BOTTOM / 2, pipe);
    drawNewPipe(firstPipe.dimensionsInPx());
}

void View::changePipeUI() {
    int position = controller.getPosition();
    if (position != 0)
        dotRect->y += SCREEN_HEIGHT / 5;
    else
        dotRect->y = 25;

}

void View::newPool() {
    std::vector<Pipe> pool = controller.newPool();
    int counter = 0;
    for (TextureWithDestination element: poolTextures) {
        delete (element.getRect());
        SDL_DestroyTexture(element.getTexture());
    }
    poolTextures.clear();
    for (Pipe pipe: pool) {
        PipeUI pipeUi = PipeUI();
        PositionedPipe positioned = PositionedPipe(SCREEN_WIDTH + OFFSET_X_POOL,
                                                   OFFSET_Y + counter * SCREEN_HEIGHT / PIPE_POOL,
                                                   pipe);
        pipeUi.setDest(positioned.getPosition());
        pipeUi.setTypeFromPipe(positioned.getPipe());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, loadedBitmaps[pipeUi.getType()]);
        TextureWithDestination newTexWithDest = TextureWithDestination(texture, pipeUi.getRect());
        poolTextures.push_back(newTexWithDest);
        SDL_QueryTexture(texture, nullptr, nullptr, &poolTextures.back().getRect()->w,
                         &poolTextures.back().getRect()->h);
        pipeUi.scale();
        counter++;
    }
}

void View::clockInit() {
    for (int i = 0; i < 2; i++) {
        auto *clockDigit = new SDL_Rect();
        clockDigit->x = SCREEN_WIDTH + OFFSET_CLOCK_X + i * 15;
        clockDigit->y = OFFSET_CLOCK_Y;
        SDL_Texture *digitTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["0"]);
        digitRects.push_back(clockDigit);
        digitTextures.push_back(digitTexture);
        SDL_QueryTexture(digitTexture, nullptr, nullptr, &clockDigit->w, &clockDigit->h);
        TextureWithDestination digitWithDest = TextureWithDestination(digitTexture, clockDigit);
        timerDigits.push_back(digitWithDest);
    }

    twoDotRect = new SDL_Rect();
    twoDotRect->x = SCREEN_WIDTH + OFFSET_CLOCK_X + 2 * 15;
    twoDotRect->y = OFFSET_CLOCK_Y;
    twoDotTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["twoDots"]);
    SDL_QueryTexture(twoDotTexture, nullptr, nullptr, &twoDotRect->w, &twoDotRect->h);

    for (int i = 3; i < 5; i++) {
        auto *clockDigit = new SDL_Rect();
        clockDigit->x = SCREEN_WIDTH + OFFSET_CLOCK_X + i * 15;
        clockDigit->y = OFFSET_CLOCK_Y;
        SDL_Texture *digitTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["0"]);
        digitRects.push_back(clockDigit);
        digitTextures.push_back(digitTexture);
        SDL_QueryTexture(digitTexture, nullptr, nullptr, &clockDigit->w, &clockDigit->h);
        TextureWithDestination digitWithDest = TextureWithDestination(digitTexture, clockDigit);
        timerDigits.push_back(digitWithDest);
    }
}


void View::timeUi(const Time &time) {
    for (int i = 0; i < 4; i++) {
        SDL_Rect *clockDigit = digitRects[i];
        int j = i;
        if (i >= 2)
            j++;
        clockDigit->x = SCREEN_WIDTH + OFFSET_CLOCK_X + j * 15;
        clockDigit->y = OFFSET_CLOCK_Y;
        int digitNumber = time.getDigit(i);
        SDL_DestroyTexture(digitTextures[i]);
        digitTextures[i] = SDL_CreateTextureFromSurface(rend, loadedBitmaps[std::to_string(digitNumber)]);
        SDL_Texture *digitTexture = digitTextures[i];
        SDL_QueryTexture(digitTexture, nullptr, nullptr, &clockDigit->w, &clockDigit->h);
        timerDigits[i] = TextureWithDestination(digitTexture, clockDigit);
    }

}

void View::drawAllPipes() {
    for (TextureWithDestination textureDTO: pipesUiTextures)
        SDL_RenderCopy(rend, textureDTO.getTexture(), nullptr, textureDTO.getRect());
}

void View::drawPool() {
    for (TextureWithDestination textureDTO: poolTextures)
        SDL_RenderCopy(rend, textureDTO.getTexture(), nullptr, textureDTO.getRect());
}

void View::drawTimer() {
    for (TextureWithDestination digitTexture: timerDigits)
        SDL_RenderCopy(rend, digitTexture.getTexture(), nullptr, digitTexture.getRect());
}

void View::drawPointer() {
    SDL_RenderCopy(rend, pointerTexture, nullptr, pointerRect);
}

void View::drawPoolDot() {
    SDL_RenderCopy(rend, dotTexture, nullptr, dotRect);
}

void View::initBitmaps() {
    loadedBitmaps["0"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/0.bmp");
    loadedBitmaps["1"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/1.bmp");
    loadedBitmaps["2"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/2.bmp");
    loadedBitmaps["3"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/3.bmp");
    loadedBitmaps["4"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/4.bmp");
    loadedBitmaps["5"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/5.bmp");
    loadedBitmaps["6"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/6.bmp");
    loadedBitmaps["7"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/7.bmp");
    loadedBitmaps["8"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/8.bmp");
    loadedBitmaps["9"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/9.bmp");
    loadedBitmaps["pointer"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/pointer.bmp");
    loadedBitmaps["dot"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/green_dot.bmp");
    loadedBitmaps["lt"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lt.bmp");
    loadedBitmaps["tr"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/tr.bmp");
    loadedBitmaps["rb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/rb.bmp");
    loadedBitmaps["lb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lb.bmp");
    loadedBitmaps["ltr"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/ltr.bmp");
    loadedBitmaps["trb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/trb.bmp");
    loadedBitmaps["lrb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lrb.bmp");
    loadedBitmaps["ltb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/ltb.bmp");
    loadedBitmaps["ltrb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/ltrb.bmp");
    loadedBitmaps["lr"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lr.bmp");
    loadedBitmaps["tb"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/tb.bmp");
    loadedBitmaps["l"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/l.bmp");
    loadedBitmaps["t"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/t.bmp");
    loadedBitmaps["r"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/r.bmp");
    loadedBitmaps["b"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/b.bmp");
    loadedBitmaps["score"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/score.bmp");
    loadedBitmaps["freeEnds"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/remaining.bmp");
    loadedBitmaps["start"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/start.bmp");
    loadedBitmaps["end"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/start.bmp");
    loadedBitmaps["twoDots"] = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/twoDots.bmp");
}

void View::dotInit() {
    dotRect = new SDL_Rect();
    dotRect->x = SCREEN_WIDTH + OFFSET_X_POINT;
    dotRect->y = OFFSET_Y;
    dotTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["dot"]);
    SDL_QueryTexture(dotTexture, nullptr, nullptr, &dotRect->w, &dotRect->h);
}

void View::pointerInit() {
    pointerRect = new SDL_Rect();
    pointerRect->x = 0;
    pointerRect->y = 0;
    pointerTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["pointer"]);
    SDL_QueryTexture(pointerTexture, nullptr, nullptr, &pointerRect->w, &pointerRect->h);
    pointerRect->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
    pointerRect->w = SCREEN_WIDTH / LIMIT_RIGHT;
}

void View::scoreInit() {
    scoreTitleRect = new SDL_Rect();
    scoreTitleRect->x = SCREEN_WIDTH + OFFSET_SCORE_X;
    scoreTitleRect->y = OFFSET_SCORE_Y;
    scoreTitleTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["score"]);
    SDL_QueryTexture(scoreTitleTexture, nullptr, nullptr, &scoreTitleRect->w, &scoreTitleRect->h);
    for (int i = 0; i < MAX_DIGITS; i++) {
        auto *scoreDigit = new SDL_Rect();
        scoreDigit->x = SCREEN_WIDTH + OFFSET_SCORE_X + scoreTitleRect->w + 5 + i * 15;
        scoreDigit->y = OFFSET_SCORE_Y;
        SDL_Texture *digitTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["0"]);
        scoreDigitRects.push_back(scoreDigit);
        scoreDigitTextures.push_back(digitTexture);
        SDL_QueryTexture(digitTexture, nullptr, nullptr, &scoreDigit->w, &scoreDigit->h);
        TextureWithDestination digitWithDest = TextureWithDestination(digitTexture, scoreDigit);
        scoreDigits.push_back(digitWithDest);
    }
}

void View::initFreeEnds() {
    freeEndsTitleRect = new SDL_Rect();
    freeEndsTitleRect->x = SCREEN_WIDTH + OFFSET_SCORE_X;
    freeEndsTitleRect->y = OFFSET_FREE_ENDS_Y;
    freeEndsTitleTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["freeEnds"]);
    SDL_QueryTexture(freeEndsTitleTexture, nullptr, nullptr, &freeEndsTitleRect->w, &freeEndsTitleRect->h);
    for (int i = 0; i < MAX_DIGITS; i++) {
        auto *freeEndsDigitRect = new SDL_Rect();
        freeEndsDigitRect->x = SCREEN_WIDTH + OFFSET_SCORE_X + freeEndsTitleRect->w + 5 + i * 15;
        freeEndsDigitRect->y = OFFSET_FREE_ENDS_Y;
        SDL_Texture *digitTexture;
        if (i != MAX_DIGITS - 1)
            digitTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["0"]);
        else
            digitTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["4"]);
        freeEndRects.push_back(freeEndsDigitRect);
        freeEndTextures.push_back(digitTexture);
        SDL_QueryTexture(digitTexture, nullptr, nullptr, &freeEndsDigitRect->w, &freeEndsDigitRect->h);
        TextureWithDestination digitWithDest = TextureWithDestination(digitTexture, freeEndsDigitRect);
        freeEndDigits.push_back(digitWithDest);
    }
}

void View::initRenderer() {
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    rend = SDL_CreateRenderer(window, -1, render_flags);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_GetWindowSurface(window);
}

void View::dummyInit() {
    window = nullptr;
    rend = nullptr;
    pointerTexture = nullptr;
    pointerRect = nullptr;
    dotRect = nullptr;
    dotTexture = nullptr;
    scoreTitleRect = nullptr;
    scoreTitleTexture = nullptr;
    freeEndsTitleRect = nullptr;
    freeEndsTitleTexture = nullptr;
}

void View::drawScoreTitle() {
    SDL_RenderCopy(rend, scoreTitleTexture, nullptr, scoreTitleRect);
}

void View::drawResult() {
    for (TextureWithDestination scoreDigit: scoreDigits)
        SDL_RenderCopy(rend, scoreDigit.getTexture(), nullptr, scoreDigit.getRect());
}

void View::drawRemaining() {
    SDL_RenderCopy(rend, freeEndsTitleTexture, nullptr, freeEndsTitleRect);
    for (TextureWithDestination digit: freeEndDigits)
        SDL_RenderCopy(rend, digit.getTexture(), nullptr, digit.getRect());
}

Positions View::getGoalPositions() const {
    return {controller.startingPosition(), controller.endingPosition()};
}


void View::goalsInit() {
    Positions goalPositions = getGoalPositions();
    goalPositions.getStart().scale();
    goalPositions.getAnEnd().scale();

    startRect = new SDL_Rect();
    endRect = new SDL_Rect();

    startRect->x = goalPositions.getStart().getX();
    startRect->y = goalPositions.getStart().getY();
    startTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["start"]);

    endRect->x = goalPositions.getAnEnd().getX();
    endRect->y = goalPositions.getAnEnd().getY();
    endTexture = SDL_CreateTextureFromSurface(rend, loadedBitmaps["end"]);

    SDL_QueryTexture(endTexture, nullptr, nullptr, &endRect->w, &endRect->h);
    SDL_QueryTexture(startTexture, nullptr, nullptr, &startRect->w, &startRect->h);

    endRect->w = SCREEN_WIDTH / LIMIT_RIGHT;
    endRect->h = SCREEN_HEIGHT / LIMIT_BOTTOM;

    startRect->w = SCREEN_WIDTH / LIMIT_RIGHT;
    startRect->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
}

void View::drawGoalPositions() {
    SDL_RenderCopy(rend, startTexture, nullptr, startRect);
    SDL_RenderCopy(rend, endTexture, nullptr, endRect);
}

void View::drawTowDots() {
    SDL_RenderCopy(rend, twoDotTexture, nullptr, twoDotRect);
}
