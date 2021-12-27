//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_GAME_H
#define WPIPES_GAME_H


#include <vector>
#include "PositionedPipe.h"
#include "Time.h"
#include "../common/Constants.h"

enum Direction {
    left, up, right, down
};

enum TimeAction {
    penalty, add, secondDown
};

class Game {
    bool started;
    std::vector<PositionedPipe> pipes;
    int freeHoles;
    int *position;
    std::vector<Pipe> pipePool;
    PositionedPipe *toDraw;
    Point pointer;
    int start;
    int end;
    int points;
    Pipe nextPipe;
    Time gameTime = Time(START_TIME);

    void addPipe(PositionedPipe &pipe);

    bool validateAndCalculateConnections(PositionedPipe &pipe);

    void setFreeHoles(int diff);

    bool isLegitMove(Direction &direction) const;

    PositionedPipe setFirstPipe();

public:
    void startGame();

    void endGame();

    bool isPlaying() const;

    void generateNextPipe();

    bool setDummyPipeAndCheck();

    bool movePointer(Direction direction);

    bool alreadyExistsThere() const;

    int getFreeEnds() const;

    int getPoints() const;

    void changeNext();

    PositionedPipe lastToDraw() const;

    Game();

    int getNumberOfSetPipes() const;

    int getPosition() const;

    std::vector<Pipe> getPool() const;

    Time getTime() const;

    void updateTime(TimeAction action);
};


#endif //WPIPES_GAME_H
