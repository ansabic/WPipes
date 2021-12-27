//
// Created by antonio on 19. 12. 2021..
//

#include "Controller.h"
#include <SDL_events.h>

Controller::Controller(const Game &game) {
    this->game = game;
    time(&myTime);
}

void Controller::begin() {
    game.startGame();
}

bool Controller::isPlaying() const {
    return game.isPlaying();
}

Action Controller::checkState(unsigned int input) {
    Action action;
    if (input == SDL_SCANCODE_UP || input == SDL_SCANCODE_W)
        action = game.movePointer(up) ? movedUp : showErrorMovement;
    else if (input == SDL_SCANCODE_S || input == SDL_SCANCODE_DOWN)
        action = game.movePointer(down) ? movedDown : showErrorMovement;
    else if (input == SDL_SCANCODE_A || input == SDL_SCANCODE_LEFT)
        action = game.movePointer(left) ? movedLeft : showErrorMovement;
    else if (input == SDL_SCANCODE_D || input == SDL_SCANCODE_RIGHT)
        action = game.movePointer(right) ? movedRight : showErrorMovement;
    else if (input == SDL_SCANCODE_RETURN || input == SDL_SCANCODE_SPACE)
        action = game.setDummyPipeAndCheck() ? hitEnterOrSpace : showErrorPlacement;
    else if (input == SDL_SCANCODE_LSHIFT || input == SDL_SCANCODE_RSHIFT) {
        pickNext();
        action = changedPipe;
    } else
        action = neutral;
    if (checkCount())
        action = gameEndedFull;

    return action;
}

GameStateDTO Controller::getState() const {
    return {game.getFreeEnds(), game.getPoints(), game.lastToDraw()};
}

bool Controller::checkCount() {
    if (game.getNumberOfSetPipes() >= LIMIT_BOTTOM * LIMIT_RIGHT) {
        game.endGame();
        return true;
    } else
        return false;
}

void Controller::pickNext() {
    game.changeNext();
}

int Controller::getPosition() const {
    return game.getPosition();
}

std::vector<Pipe> Controller::newPool() const {
    return game.getPool();
}

Time Controller::timeFlies() {
    time_t now;
    time(&now);
    if ((now - myTime) >= 1) {
        myTime = now;
        game.updateTime(secondDown);
    }
    return game.getTime();
}

void Controller::timePenalty() {
    game.updateTime(penalty);
}

void Controller::rewardTime() {
    game.updateTime(add);
}

void Controller::timeOut() {
    game.stop();
}

Point Controller::startingPosition() const {
    return game.startingPosition();
}

Point Controller::endingPosition() const {
    return game.endingPosition();
}

