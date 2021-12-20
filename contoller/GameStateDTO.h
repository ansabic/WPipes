//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_GAMESTATEDTO_H
#define WPIPES_GAMESTATEDTO_H


#include "../model/PositionedPipe.h"

class GameStateDTO {
public:
    int freeEnds;
    int score;
    PositionedPipe newPipe;

    GameStateDTO(int freeEnds, int score, PositionedPipe newPipe) : freeEnds(freeEnds), score(score), newPipe(newPipe) {

    }

};


#endif //WPIPES_GAMESTATEDTO_H
