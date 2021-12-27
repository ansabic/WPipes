//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_GAMESTATEDTO_H
#define WPIPES_GAMESTATEDTO_H


#include "../model/PositionedPipe.h"
#include "../view/Positions.h"

class GameStateDTO {
public:
    int freeEnds;
    int score;
    PositionedPipe newPipe;
    bool solvedStart;
    bool solvedEnd;

    GameStateDTO(int freeEnds, int score, PositionedPipe newPipe, bool start, bool end) : freeEnds(freeEnds),
                                                                                          score(score),
                                                                                          newPipe(newPipe),
                                                                                          solvedStart(start),
                                                                                          solvedEnd(end) {

    }

};


#endif //WPIPES_GAMESTATEDTO_H
