//
// Created by antonio on 27. 12. 2021..
//

#include "Time.h"

Time::Time(int from) {
    minutes = Number(from / 60);
    seconds = Number(from % 60);
}

int Time::getValue() const {
    return minutes.value() * 60 + seconds.value();
}

void Time::addSeconds(int other) {
    int newSeconds = seconds.value() + other;
    int result = minutes.value() * 60 + newSeconds;
    *this = Time(result);
}

Time Time::operator-(int toSubtract) const {
    int result = getValue() - toSubtract;
    if (result < 0)
        return Time(0);
    return Time(result);
}

int Time::getDigit(int position) const {
    int result = 0;
    switch (position) {
        case 0:
            result = minutes.value() / 10;
            break;
        case 1:
            result = minutes.value() % 10;
            break;
        case 2:
            result = seconds.value() / 10;
            break;
        case 3:
            result = seconds.value() % 10;
            break;
        default:
            result = 0;
    }
    return result;
}

bool Time::isDone() const {
    if (minutes.value() == 0 && seconds.value() == 0)
        return true;
    else
        return false;
}
