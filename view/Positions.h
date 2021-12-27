//
// Created by antonio on 27. 12. 2021..
//

#ifndef WPIPES_POSITIONS_H
#define WPIPES_POSITIONS_H


#include "../model/Point.h"

class Positions {
    Point start;
    Point end;
public:
    Positions(const Point &start, const Point &anEnd);

    Point &getStart();

    void setStart(const Point &newStart);

    Point &getAnEnd();

    void setAnEnd(const Point &anEnd);
};


#endif //WPIPES_POSITIONS_H
