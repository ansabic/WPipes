//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_GAME_H
#define WPIPES_GAME_H


#include <vector>
#include "PositionedPipe.h"

enum Direction {
    left, up, right, down
};

class Game {
    bool started;
    std::vector<PositionedPipe> pipes;
    int freeHoles;
    Pipe nextPipe;
    Point pointer;
    int start;
    int end;
    int points;

    void addPipe(PositionedPipe &pipe);

    bool validateAndCalculateConnections(PositionedPipe &pipe);

    void setFreeHoles(int diff);

    bool isLegitMove(Direction &direction) const;

public:
    void startGame();

    void endGame();

    bool isPlaying() const;

    void generateNextPipe();

    bool setDummyPipeAndCheck();

    bool movePointer(Direction direction);

    bool alreadyExistsThere() const;

    int getFreeEnds() const;

    Point getPointer() const;

    int getPoints() const;

    PositionedPipe getLastAdded() const;

    Game();

    int getNumberOfSetPipes() const;

    PositionedPipe setFirstPipe();
};


#endif //WPIPES_GAME_H
