//
// Created by antonio on 22. 12. 2021..
//

#include "PipeUI.h"

void PipeUI::setTypeFromPipe(Pipe pipe) {
    bool l = pipe.getLeft();
    bool t = pipe.getTop();
    bool r = pipe.getRight();
    bool b = pipe.getBottom();

    const SDL_Surface *lt = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lt.bmp");
    const SDL_Surface *tr = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/tr.bmp");
    const SDL_Surface *rb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/rb.bmp");
    const SDL_Surface *lb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lb.bmp");
    const SDL_Surface *ltr = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/ltr.bmp");
    const SDL_Surface *trb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/trb.bmp");
    const SDL_Surface *lrb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lrb.bmp");
    const SDL_Surface *ltb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/ltb.bmp");
    const SDL_Surface *ltrb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/ltrb.bmp");
    const SDL_Surface *lr = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/lr.bmp");
    const SDL_Surface *tb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/tb.bmp");
    const SDL_Surface *ll = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/l.bmp");
    const SDL_Surface *tt = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/t.bmp");
    const SDL_Surface *rr = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/r.bmp");
    const SDL_Surface *bb = SDL_LoadBMP("/home/antonio/CLionProjects/WPipes/assets/b.bmp");


    type = new SDL_Surface();
    if (l && !t && !r && !b) {
        *type = *ll;
        return;
    } else if (!l && t && !r && !b) {
        *type = *tt;
        return;
    } else if (!l && !t && r && !b) {
        *type = *rr;
        return;
    } else if (!l && !t && !r && b) {
        *type = *bb;
        return;
    } else if (l && r && !t && !b) {
        *type = *lr;
        return;
    } else if (l && t && !r && !b) {
        *type = *lt;
        return;
    } else if (l && b && !t && !r) {
        *type = *lb;
        return;
    } else if (t && r && !b && !l) {
        *type = *tr;
        return;
    } else if (t && b && !r && !l) {
        *type = *tb;
        return;
    } else if (r && b && !t && !l) {
        *type = *rb;
        return;
    } else if (l && t && r && !b) {
        *type = *ltr;
        return;
    } else if (l && t && b && !r) {
        *type = *ltb;
        return;
    } else if (l && r && b && !t) {
        *type = *lrb;
        return;
    } else if (t && r && b && !l) {
        *type = *trb;
        return;
    } else if (l && r && b && t) {
        *type = *ltrb;
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

SDL_Surface *PipeUI::getSurface() const {
    return type;
}

SDL_Rect *PipeUI::getRect() const {
    return dest;
}

void PipeUI::scale() {
    dest->h = SCREEN_HEIGHT / LIMIT_BOTTOM;
    dest->w = SCREEN_WIDTH / LIMIT_RIGHT;
}
