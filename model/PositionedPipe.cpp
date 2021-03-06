//
// Created by antonio on 19. 12. 2021..
//

#include "PositionedPipe.h"
#include "../common/Constants.h"

PositionedPipe::PositionedPipe(int x, int y, Pipe &pipe) : position(Point(x, y)) {
    setPipe(pipe);
}

bool PositionedPipe::updateIfLegit(PositionedPipe &other, int *freeHoles, Point *start, Point *end, bool *startSolved,
                                   bool *endSolved) {
    if (Point::areWithinLimits(position, other.position)) {
        if ((!*startSolved) && position == *start)
            *startSolved = true;
        if ((!*endSolved) && position == *end)
            *endSolved = true;
        if (checkIfCompatibleSidesAndResetEnds(other, freeHoles))
            return true;
        else
            return false;
    } else
        return false;
}

bool PositionedPipe::checkIfCompatibleSidesAndResetEnds(PositionedPipe &other, int *freeHoles) {
    if (position.isNeighbor(other.position)) {
        Point p1 = position;
        Point p2 = other.position;
        PointRelation relation = p1 - p2;
        switch (relation) {
            case leftFrom:
                if (getRight() && other.getLeft()) {
                    setRight();
                    other.setLeft();
                    (*freeHoles)--;
                    return true;
                } else
                    return false;
            case upFrom:
                if (getBottom() && other.getTop()) {
                    setBottom();
                    other.setTop();
                    (*freeHoles)--;
                    return true;
                } else
                    return false;
            case rightFrom:
                if (getLeft() && other.getRight()) {
                    setLeft();
                    other.setRight();
                    (*freeHoles)--;
                    return true;
                } else
                    return false;
            case downFrom:
                if (getTop() && other.getBottom()) {
                    setTop();
                    other.setBottom();
                    (*freeHoles)--;
                    return true;
                } else
                    return false;
            default:
                return false;
        }
    } else
        return false;
}

Point PositionedPipe::getPosition() const {
    return position;
}

int PositionedPipe::getFreeEnds() const {
    int counter = 0;
    if (getBottom())
        ++counter;
    if (getTop())
        ++counter;
    if (getLeft())
        ++counter;
    if (getRight())
        ++counter;
    return counter;
}

PositionedPipe PositionedPipe::dimensionsInPx() const {
    Pipe tempPipe = getPipe();
    PositionedPipe properDimensions = PositionedPipe(getPosition().getX() * SCREEN_WIDTH / LIMIT_RIGHT,
                                                     getPosition().getY() * SCREEN_HEIGHT / LIMIT_BOTTOM,
                                                     tempPipe);
    return properDimensions;
}

void PositionedPipe::updatePipe(Pipe &pipe) {
    setPipe(pipe);
}



