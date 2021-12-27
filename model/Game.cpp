//
// Created by antonio on 19. 12. 2021..
//
#include "Game.h"

void Game::startGame() {
    started = true;
}

void Game::endGame() {
    started = false;
}

void Game::addPipe(PositionedPipe &pipe) {
    pipes.push_back(pipe);
    generateNextPipe();
    points += NEW_PIPE_POINTS;
}

bool Game::movePointer(Direction direction) {
    if (isLegitMove(direction)) {
        switch (direction) {
            case left:
                pointer.minusX();
                return true;
            case up:
                pointer.minusY();
                return true;
            case right:
                pointer.addX();
                return true;
            case down:
                pointer.addY();
                return true;
        }
    } else
        return false;
    return false;
}

bool Game::isLegitMove(Direction &direction) const {
    if (pointer.getX() == LIMIT_LEFT && direction == left ||
        pointer.getX() == LIMIT_RIGHT - 1 && direction == right ||
        pointer.getY() == LIMIT_UP && direction == up ||
        pointer.getY() == LIMIT_BOTTOM - 1 && direction == down)
        return false;
    else
        return true;
}

bool Game::alreadyExistsThere() const {
    for (PositionedPipe pipe: pipes) {
        if (pointer == pipe.getPosition())
            return true;
    }
    return false;
}

bool Game::validateAndCalculateConnections(PositionedPipe &pipe) {
    bool everythingOk;
    *toDraw = pipe;
    for (PositionedPipe tempPipe: pipes) {
        bool result = tempPipe.updateIfLegit(pipe, &freeHoles);
        everythingOk = everythingOk || result;
    }
    if (everythingOk) {
        addPipe(pipe);
        setFreeHoles(pipe.getFreeEnds());
    }
    return everythingOk;
}

void Game::setFreeHoles(int diff) {
    freeHoles += diff;
}

bool Game::setDummyPipeAndCheck() {
    PositionedPipe pipe = PositionedPipe(pointer.getX(), pointer.getY(), nextPipe);
    if (alreadyExistsThere())
        return false;
    else
        return validateAndCalculateConnections(pipe);
}

void Game::generateNextPipe() {
    pipePool.clear();
    for (int i = 0; i < PIPE_POOL; i++) {
        Pipe dummyPipe = Pipe();
        pipePool.push_back(dummyPipe);
    }
    nextPipe = pipePool[*position];
}

Game::Game() {
    position = new int;
    setFirstPipe();
    started = false;
    freeHoles = 4;
    *position = 0;
    nextPipe = pipePool[*position].getPipe();
    pointer = Point(0, 0);
    start = (int) random() % (LIMIT_BOTTOM * 2 + LIMIT_RIGHT * 2);
    int result = (int) random() % (LIMIT_BOTTOM * 2 + LIMIT_RIGHT * 2);
    while (result == start)
        result = (int) random() % (LIMIT_BOTTOM * 2 + LIMIT_RIGHT * 2);
    end = result;
    points = 0;
    toDraw = new PositionedPipe(0, 0, nextPipe);
    *toDraw = PositionedPipe(0, 0, nextPipe);
}

bool Game::isPlaying() const {
    return started;
}

int Game::getFreeEnds() const {
    return freeHoles;
}

int Game::getPoints() const {
    return points;
}

PositionedPipe Game::lastToDraw() const {
    return *toDraw;
}

int Game::getNumberOfSetPipes() const {
    return (int) pipes.size();
}

PositionedPipe Game::setFirstPipe() {
    Pipe allFour = Pipe(true);
    PositionedPipe firstPipe = PositionedPipe(LIMIT_RIGHT / 2, LIMIT_BOTTOM / 2, allFour);
    addPipe(firstPipe);
    setFreeHoles(firstPipe.getFreeEnds());
    generateNextPipe();
    return firstPipe;
}

void Game::changeNext() {
    if (*position < PIPE_POOL - 1)
        (*position)++;
    else
        *position = 0;
    nextPipe = pipePool[*position];
}

int Game::getPosition() const {
    return *position;
}

std::vector<Pipe> Game::getPool() const {
    return pipePool;
}

Time Game::getTime() const {
    return gameTime;
}

void Game::updateTime(TimeAction action) {
    switch (action) {
        case penalty:
            gameTime = gameTime - PENALTY_TIME;
            break;
        case add:
            gameTime.addSeconds(GIFT_TIME);
            break;
        case secondDown:
            gameTime = gameTime - 1;
            break;
    }
}


