//
// Created by antonio on 19. 12. 2021..
//

#include "Controller.h"
#include "../common/Constants.h"
#include <SDL_events.h>

Controller::Controller(const Game &game) {
    this->game = game;
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
    else if (input == SDL_SCANCODE_RETURN || input == SDL_SCANCODE_SPACE) {
        action = game.setDummyPipeAndCheck() ? hitEnterOrSpace : showErrorPlacement;
    } else
        action = neutral;
    if (checkCount())
        action = gameEndedFull;

    return action;
}

GameStateDTO Controller::getState() const {
    return {game.getFreeEnds(), game.getPoints(), game.getLastAdded()};
}

bool Controller::checkCount() {
    if (game.getNumberOfSetPipes() >= LIMIT_BOTTOM * LIMIT_RIGHT) {
        game.endGame();
        return true;
    } else
        return false;
}

PositionedPipe Controller::placeFirstPipe() {
    return game.setFirstPipe();
}

