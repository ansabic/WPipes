//
// Created by antonio on 19. 12. 2021..
//

#include <valarray>
#include "Point.h"
#include "../common/CommonFunctions.h"
#include "../common/Constants.h"

Point::Point(int newX, int newY) {
    x = newX;
    y = newY;
}

PointRelation Point::operator-(Point other) const {
    if (x == other.x) {
        if (y > other.y)
            return upFrom;
        else if (y < other.y)
            return downFrom;
        else
            return same;
    } else if (y == other.y) {
        if (x > other.x)
            return rightFrom;
        if (x < other.x)
            return leftFrom;
        else
            return same;
    } else
        return PointRelation::other;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

bool Point::isNeighbor(Point other) const {
    int xDiff = abs(other.getX() - getX());
    int yDiff = abs(other.getY() - getY());
    if ((xDiff == 1 && yDiff == 0) || (xDiff == 0 && yDiff == 1))
        return true;
    else
        return false;
}

bool Point::areWithinLimits(Point &p1, Point &p2) {
    int maxX = CommonFunctions::max(p1.getX(), p2.getX());
    int maxY = CommonFunctions::max(p1.getY(), p2.getY());
    int minX = CommonFunctions::min(p1.getX(), p2.getX());
    int minY = CommonFunctions::min(p1.getY(), p2.getY());
    if (maxX < LIMIT_RIGHT && minX > LIMIT_LEFT && maxY < LIMIT_BOTTOM && minY > LIMIT_UP)
        return true;
    else
        return false;
}

void Point::minusX() {
    --x;
}

void Point::minusY() {
    --y;
}

void Point::addX() {
    ++x;
}

void Point::addY() {
    ++y;
}

bool Point::operator==(Point other) const {
    if (x == other.getX() && other.getY() == other.getY())
        return true;
    else
        return false;
}

Point::Point() {
    x = 0;
    y = 0;
}



