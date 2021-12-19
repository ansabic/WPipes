//
// Created by antonio on 19. 12. 2021..
//

#include "View.h"
#include <ncurses.h>

View::View(Controller& controller): controller(controller) {

}

void View::loop() {
    controller.begin();
    while(controller.isPlaying()) {
        listenForClicks();
    }
}

void View::listenForClicks() {
    int input = getch();
    Action result = controller.checkPressedKey(input);
    switch (result) {

        case movedUp:
            break;
        case movedDown:
            break;
        case movedLeft:
            break;
        case movedRight:
            break;
        case hitEnterOrSpace:
            break;
        case showErrorMovement:
            break;
        case showErrorPlacement:
            break;
    }
    showError(!everythingGood);
}
void View::showError(bool shouldShow) {
    if(shouldShow) {
        //TODO Show error with OpenGL
    }
}

