//
// Created by antonio on 19. 12. 2021..
//

#include "Pipe.h"
#include "../common/CommonFunctions.h"


Pipe::Pipe(bool first) {
    if (!first) {
        openLeft = CommonFunctions::randomBool();
        openTop = CommonFunctions::randomBool();
        openRight = CommonFunctions::randomBool();
        openBottom = CommonFunctions::randomBool();
    } else {
        openLeft = true;
        openBottom = true;
        openRight = true;
        openTop = true;
    }
}

Pipe Pipe::getPipe() const {
    return *this;
}

bool Pipe::getLeft() const {
    return openLeft;
}

bool Pipe::getRight() const {
    return openRight;
}

bool Pipe::getTop() const {
    return openTop;
}

bool Pipe::getBottom() const {
    return openBottom;
}

void Pipe::setBottom() {
    openBottom = false;
}

void Pipe::setTop() {
    openTop = false;
}

void Pipe::setRight() {
    openRight = false;
}

void Pipe::setLeft() {
    openLeft = false;
}

Pipe::Pipe(bool openLeft, bool openTop, bool openRight, bool openBottom) {
    this->openLeft = openLeft;
    this->openRight = openRight;
    this->openTop = openTop;
    this->openBottom = openBottom;
}

void Pipe::setPipe(Pipe &pipe) {
    *this = pipe;
}

