//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_CONTROLLER_H
#define WPIPES_CONTROLLER_H


#include "../model/Game.h"

enum Action { movedUp, movedDown, movedLeft, movedRight, hitEnterOrSpace, showErrorMovement, showErrorPlacement, neutral };

class Controller {
    Game game;
public:
    explicit Controller(const Game& game);

    void begin();
    bool isPlaying() const;
    Action checkPressedKey(int input);
};


#endif //WPIPES_CONTROLLER_H
