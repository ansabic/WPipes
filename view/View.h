//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_VIEW_H
#define WPIPES_VIEW_H


#include "../contoller/Controller.h"

class View {
    Controller controller;
    void listenForClicks();
    static void showError(bool shouldShow);
public:
    explicit View(Controller& controller);
    void loop();

};


#endif //WPIPES_VIEW_H
