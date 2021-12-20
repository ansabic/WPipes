//
// Created by antonio on 19. 12. 2021..
//

#include "Controller.h"
#include "../common/Constants.h"
#include <ncurses.h>

Controller::Controller(const Game &game) {
    this->game = game;
}

void Controller::begin() {
    game.startGame();
}

bool Controller::isPlaying() const {
    return game.isPlaying();
}

Action Controller::checkState(int input) {
    const char SPACE = ' ';
    Action action;
    if (input == KEY_UP)
        action = game.movePointer(up) ? movedUp : showErrorMovement;
    else if (input == KEY_DOWN)
        action = game.movePointer(down) ? movedDown : showErrorMovement;
    else if (input == KEY_LEFT)
        action = game.movePointer(left) ? movedLeft : showErrorMovement;
    else if (input == KEY_RIGHT)
        action = game.movePointer(right) ? movedRight : showErrorMovement;
    else if (input == KEY_ENTER || input == SPACE) {
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
