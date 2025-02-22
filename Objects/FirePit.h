//
// Created by VidBe on 22/02/2025.
//

#ifndef FIREPIT_H
#define FIREPIT_H
#include <iostream>

#include "GameObject.h"


class FirePit : GameObject{
    int spriteColumn = 0;
    int spriteRow = 0;
    int spriteTimer;

public:
    using GameObject::GameObject; //Inherits constructor from base class

    void animateSprite(const int spriteTimerReset, const int spriteColumnReset) {
        spriteTimer++;
        if (spriteTimer >= spriteTimerReset) {
            spriteColumn++;
            spriteTimer = 0;
        }
        if (spriteColumn >= spriteColumnReset) {
            spriteColumn = 0;
        }
        objectSprite.setTextureRect(sf::IntRect({spriteColumn*64,spriteRow*64},{64,64}));
    }

    sf::Sprite getSprite() {
        return objectSprite;
    }
};



#endif //FIREPIT_H
