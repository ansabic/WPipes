//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_CONTROLLER_H
#define WPIPES_CONTROLLER_H


#include "../model/Game.h"
#include "GameStateDTO.h"

enum Action {
    movedUp,
    movedDown,
    movedLeft,
    movedRight,
    hitEnterOrSpace,
    showErrorMovement,
    showErrorPlacement,
    neutral,
    changedPipe,
    gameEndedFull
};

class Controller {
    Game game;
public:
    explicit Controller(const Game &game);

    void begin();

    bool isPlaying() const;

    Action checkState(unsigned int input);

    GameStateDTO getState() const;

    bool checkCount();

    void pickNext();

    int getPosition() const;

    std::vector<Pipe> newPool() const;
};


#endif //WPIPES_CONTROLLER_H
