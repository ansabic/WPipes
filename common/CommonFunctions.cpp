//
// Created by antonio on 19. 12. 2021..
//

#include <random>
#include "CommonFunctions.h"

bool CommonFunctions::randomBool() {
    return random() % 2;
}

int CommonFunctions::max(int a, int b) {
    return a > b ? a : b;
}

int CommonFunctions::min(int a, int b) {
    return a < b ? a : b;
}


