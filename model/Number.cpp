//
// Created by antonio on 27. 12. 2021..
//

#include <algorithm>
#include <valarray>
#include "Number.h"

Number Number::operator+(Number &other) const {
    int result = value() + other.value();
    return Number(result);
}

int Number::getSize() const {
    return (int) digits.size();
}

void Number::operator++() {
    int result = value() + 1;
    *this = Number(result);
}

Number::Number(int number) {
    if (number == 0)
        digits.push_back(0);
    while (number != 0) {
        int digit = number % 10;
        number /= 10;
        digits.push_back(digit);
    }
    std::reverse(digits.begin(), digits.end());
}

int Number::value() const {
    int result = 0;
    int counter = 0;
    std::vector<int> copy = digits;
    while (!copy.empty()) {
        result += copy.back() * (int) pow(10, counter);
        counter++;
        copy.pop_back();
    }
    return result;
}

void Number::operator--() {
    int result = value() - 1;
    *this = Number(result);
}

Number Number::operator/(Number &other) const {
    int result = value() / other.value();
    return Number(result);
}

int Number::getDigit(int position) const {
    return digits[position];
}

Number::Number() = default;
