//
// Created by antonio on 27. 12. 2021..
//

#ifndef WPIPES_NUMBER_H
#define WPIPES_NUMBER_H


#include <vector>

class Number {
    std::vector<int> digits;

public:
    explicit Number(int number);

    Number();

    int getSize() const;

    Number operator+(Number &other) const;

    Number operator/(Number &other) const;

    void operator++();

    void operator--();

    int value() const;

    int getDigit(int position) const;
};


#endif //WPIPES_NUMBER_H
