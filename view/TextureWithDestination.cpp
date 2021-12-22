//
// Created by antonio on 22. 12. 2021..
//

#include "TextureWithDestination.h"

SDL_Texture *TextureWithDestination::getTexture() const {
    return texture;
}

SDL_Rect *TextureWithDestination::getRect() const {
    return destination;
}
