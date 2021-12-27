//
// Created by antonio on 22. 12. 2021..
//

#include "PipeUI.h"

void PipeUI::setTypeFromPipe(Pipe pipe) {
    bool l = pipe.getLeft();
    bool t = pipe.getTop();
    bool r = pipe.getRight();
    bool b = pipe.getBottom();

    if (l && !t && !r && !b) {
        type = "l";
        return;
    } else if (!l && t && !r && !b) {
        type = "t";
        return;
    } else if (!l && !t && r && !b) {
        type = "r";
        return;
    } else if (!l && !t && !r && b) {
        type = "b";
        return;
    } else if (l && r && !t && !b) {
        type = "lr";
        return;
    } else if (l && t && !r && !b) {
        type = "lt";
        return;
    } else if (l && b && !t && !r) {
        type = "lb";
        return;
    } else if (t && r && !b && !l) {
        type = "tr";
        return;
    } else if (t && b && !r && !l) {
        type = "tb";
        return;
    } else if (r && b && !t && !l) {
        type = "rb";
        return;
    } else if (l && t && r && !b) {
        type = "ltr";
        return;
    } else if (l && t && b && !r) {
        type = "ltb";
        return;
    } else if (l && r && b && !t) {
        type = "lrb";
        return;
    } else if (t && r && b && !l) {
        type = "trb";
        return;
    } else if (l && r && b && t) {
        type = "ltrb";
        return;
    }
}

void PipeUI::setDest(Point position) {
    dest = new SDL_Rect();
    dest->x = position.getX();
    dest->y = position.getY();
    dest->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
    dest->w = SCREEN_WIDTH / LIMIT_RIGHT;
}

std::string PipeUI::getType() const {
    return type;
}

SDL_Rect *PipeUI::getRect() const {
    return dest;
}

void PipeUI::scale() {
    dest->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
    dest->w = SCREEN_WIDTH / LIMIT_RIGHT;
}
