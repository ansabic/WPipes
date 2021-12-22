//
// Created by antonio on 22. 12. 2021..
//

#ifndef WPIPES_TEXTUREWITHDESTINATION_H
#define WPIPES_TEXTUREWITHDESTINATION_H


#include <SDL_render.h>

class TextureWithDestination {
    SDL_Texture *texture;
    SDL_Rect *destination;
public:
    TextureWithDestination(SDL_Texture *tex, SDL_Rect *rect) : texture(tex), destination(rect) {

    }

    SDL_Texture *getTexture() const;

    SDL_Rect *getRect() const;
};


#endif //WPIPES_TEXTUREWITHDESTINATION_H
