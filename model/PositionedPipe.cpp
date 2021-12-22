//
// Created by antonio on 19. 12. 2021..
//

#include <cmath>
#include "PositionedPipe.h"
#include "../common/CommonFunctions.h"
#include "../common/Constants.h"

PositionedPipe::PositionedPipe(int x, int y, Pipe &pipe) : position(Point(x, y)) {
    setPipe(pipe);
}

bool PositionedPipe::updateIfLegit(PositionedPipe &other) {
    if (Point::areWithinLimits(position, other.position) && checkIfCompatibleSidesAndResetEnds(other))
        return true;
    else
        return false;
}

bool PositionedPipe::checkIfCompatibleSidesAndResetEnds(PositionedPipe &other) const {
    if (position.isNeighbor(other.position)) {
        Point p1 = position;
        Point p2 = other.position;
        PointRelation relation = p1 - p2;
        Pipe thisPipe = getPipe();
        Pipe otherPipe = other.getPipe();
        switch (relation) {
            case leftFrom:
                if (thisPipe.getRight() && otherPipe.getLeft()) {
                    thisPipe.setRight();
                    otherPipe.setLeft();
                    return true;
                } else
                    return false;
            case upFrom:
                if (thisPipe.getBottom() && otherPipe.getTop()) {
                    thisPipe.setBottom();
                    otherPipe.setTop();
                    return true;
                } else
                    return false;
            case rightFrom:
                if (thisPipe.getLeft() && otherPipe.getRight()) {
                    thisPipe.setLeft();
                    otherPipe.setRight();
                    return true;
                } else
                    return false;
            case downFrom:
                if (thisPipe.getTop() && otherPipe.getBottom()) {
                    thisPipe.setTop();
                    otherPipe.setBottom();
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



