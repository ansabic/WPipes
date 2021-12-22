//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_POSITIONEDPIPE_H
#define WPIPES_POSITIONEDPIPE_H


#include "Pipe.h"
#include "Point.h"

class PositionedPipe : public Pipe {
    Point position;

    bool checkIfCompatibleSidesAndResetEnds(PositionedPipe &other) const;

public:
    PositionedPipe(int x, int y, Pipe &pipe);

    Point getPosition() const;

    int getFreeEnds() const;

    bool updateIfLegit(PositionedPipe &other);

    PositionedPipe dimensionsInPx() const;
};


#endif //WPIPES_POSITIONEDPIPE_H
