//
// Created by antonio on 22. 12. 2021..
//

#ifndef WPIPES_PIPEUI_H
#define WPIPES_PIPEUI_H


#include <string>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include "../common/Constants.h"
#include "../model/Point.h"
#include "../model/Pipe.h"

class PipeUI {
    std::string type;
    SDL_Rect *dest;
public:
    void setTypeFromPipe(Pipe pipe);

    void setDest(Point position);

    std::string getType() const;

    SDL_Rect *getRect() const;

    void scale();
};


#endif //WPIPES_PIPEUI_H
