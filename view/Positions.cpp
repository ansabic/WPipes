//
// Created by antonio on 27. 12. 2021..
//

#include "Positions.h"

Point &Positions::getStart() {
    return start;
}

void Positions::setStart(const Point &newStart) {
    Positions::start = newStart;
}

Point &Positions::getAnEnd() {
    return end;
}

void Positions::setAnEnd(const Point &anEnd) {
    end = anEnd;
}

Positions::Positions(const Point &start, const Point &anEnd) : start(start), end(anEnd) {}
