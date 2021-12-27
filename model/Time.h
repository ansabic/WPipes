//
// Created by antonio on 27. 12. 2021..
//

#ifndef WPIPES_TIME_H
#define WPIPES_TIME_H


#include "Number.h"

class Time {
    Number minutes;
    Number seconds;

    int getValue() const;

public:
    explicit Time(int from);

    Time operator-(int toSubtract) const;

    void addSeconds(int other);

    int getDigit(int position) const;

    bool isDone() const;
};


#endif //WPIPES_TIME_H
