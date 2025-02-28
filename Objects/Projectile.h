//
// Created by VidBe on 27/02/2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <string>

#include "HitBox.h"

class HitBox;

class Projectile : GameObject{
public:
    HitBox* hitBox;
    float angle;

    Projectile(const std::string &textureFile, int textureRectSize, float hitBoxSizeX,
               float hitBoxSizeY, float hBOriginX, float hBOriginY, const GameObject& gameObject);

    void update(float deltaTime);
};



#endif //PROJECTILE_H
