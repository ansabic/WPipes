//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_POINT_H
#define WPIPES_POINT_H

enum PointRelation {
    leftFrom, upFrom, rightFrom, downFrom, same, other
};

class Point {
    int x;
    int y;
public:
    Point();
    Point(int x, int y);
    int getX() const;
    int getY() const;
    bool isNeighbor(Point other) const;
    static bool areWithinLimits(Point& p1, Point& p2);
    PointRelation operator-(Point other) const;
    bool operator==(Point other) const;
    void minusX();
    void minusY();
    void addX();
    void addY();
};


#endif //WPIPES_POINT_H
