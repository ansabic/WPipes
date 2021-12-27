//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_CONTROLLER_H
#define WPIPES_CONTROLLER_H


#include <ctime>
#include "../model/Game.h"
#include "GameStateDTO.h"
#include "../model/Time.h"
#include "../common/Constants.h"

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
    time_t myTime{};
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

    Time timeFlies();

    void timePenalty();

    void rewardTime();

    void timeOut();

    Point startingPosition() const;

    Point endingPosition() const;
};


#endif //WPIPES_CONTROLLER_H
