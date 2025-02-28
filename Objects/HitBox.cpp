//
// Created by VidBe on 27/02/2025.
//

#include "HitBox.h"

#include "GameObject.h"

HitBox::HitBox(float sizeX, float sizeY, float originX, float originY, GameObject* gameObject) {
    shape.setSize({sizeX,sizeY});
    shape.setOrigin({originX,originY});
    shape.setPosition(gameObject->getSprite().getPosition());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Red);
    value = shape.getGlobalBounds();
}
