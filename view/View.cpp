//
// Created by antonio on 19. 12. 2021..
//

#include "View.h"
#include "../common/Constants.h"
#include <curses.h>
#include <chrono>

View::View(Controller &controller) : controller(controller) {

}

void View::loop() {
    controller.begin();
    auto startTime = std::chrono::high_resolution_clock::now();
    while (controller.isPlaying()) {
        auto refTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(refTime - startTime);
        if (duration.count() >= 1000 / FPS) {
            listenForEvents();
            startTime = std::chrono::high_resolution_clock::now();
        }
    }
}

void View::listenForEvents() {
    int input = getch();
    Action result = controller.checkState(input);
    switch (result) {
        case movedUp:
            moveUp();
            break;
        case movedDown:
            moveDown();
            break;
        case movedLeft:
            moveLeft();
            break;
        case movedRight:
            moveRight();
            break;
        case hitEnterOrSpace:
            spawnNew();
            break;
        case showErrorMovement:
            movementError();
            break;
        case showErrorPlacement:
            placementError();
            break;
        case gameEndedFull:
            showGameOver();
            break;
        case neutral:
            break;
    }
}

void View::spawnNew() {
    GameStateDTO state = controller.getState();
    showResult(state.score);
    showFreeEnds(state.freeEnds);
    drawNewPipe(state.newPipe);
}

void View::moveUp() {
    //TODO OpenGL
}

void View::moveDown() {
    //TODO OpenGL
}

void View::moveLeft() {
    //TODO OpenGL
}

void View::moveRight() {
    //TODO OpenGL
}

void View::movementError() {
    //TODO OpenGL
}

void View::placementError() {
    //TODO OpenGL
}

void View::showResult(int score) {
    //TODO OpenGL
}

void View::showFreeEnds(int ends) {
    //TODO OpenGL
}

void View::drawNewPipe(PositionedPipe pipe) {
    //TODO OpenGL
}

void View::showGameOver() {
    //TODO OpenGL
}

