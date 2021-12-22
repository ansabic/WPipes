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

    PositionedPipe placeFirstPipe();
};


#endif //WPIPES_CONTROLLER_H
