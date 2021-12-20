//
// Created by antonio on 19. 12. 2021..
//

#include <random>
#include "Game.h"
#include "../common/Constants.h"

void Game::startGame() {
    started = true;
}

void Game::endGame() {
    started = false;
}

void Game::addPipe(PositionedPipe &pipe) {
    pipes.push_back(pipe);
    generateNextPipe();
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
        pointer.getX() == LIMIT_RIGHT && direction == right ||
        pointer.getY() == LIMIT_UP && direction == up ||
        pointer.getY() == LIMIT_BOTTOM && direction == down)
        return false;
    else
        return true;
}

bool Game::alreadyExistsThere() const {
    for (PositionedPipe pipe: pipes) {
        if (pointer == pipe.getPosition())
            return true;
        else
            return false;
    }
    return false;
}

bool Game::validateAndCalculateConnections(PositionedPipe &pipe) {
    bool everythingOk = false;
    for (PositionedPipe tempPipe: pipes)
        everythingOk = everythingOk || tempPipe.updateIfLegit(pipe);
    if (everythingOk)
        addPipe(pipe);

    setFreeHoles(pipe.getFreeEnds());
    return everythingOk;
}

void Game::setFreeHoles(int diff) {
    freeHoles += diff;
}

bool Game::setDummyPipeAndCheck() {
    PositionedPipe pipe = PositionedPipe(pointer.getX(), pointer.getY(), nextPipe);
    return validateAndCalculateConnections(pipe);
}

void Game::generateNextPipe() {
    nextPipe = Pipe();
}

Game::Game() {
    started = false;
    freeHoles = 0;
    nextPipe = Pipe(true, true, true, true);
    pointer = Point(0, 0);
    start = (int) random() % (LIMIT_BOTTOM * 2 + LIMIT_RIGHT * 2);
    int result = (int) random() % (LIMIT_BOTTOM * 2 + LIMIT_RIGHT * 2);
    while (result == start)
        result = (int) random() % (LIMIT_BOTTOM * 2 + LIMIT_RIGHT * 2);
    end = result;
    points = 0;
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

PositionedPipe Game::getLastAdded() const {
    return pipes.back();
}

int Game::getNumberOfSetPipes() const {
    return (int) pipes.size();
}


