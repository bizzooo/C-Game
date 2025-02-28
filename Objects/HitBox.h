//
// Created by VidBe on 27/02/2025.
//

#ifndef HITBOX_H
#define HITBOX_H
#include "GameObject.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class GameObject;

class HitBox {
public:
    sf::RectangleShape shape;
    sf::FloatRect value;

    HitBox(float sizeX, float sizeY, float originX, float originY, GameObject* gameObject);

    ~HitBox();
};



#endif //HITBOX_H
