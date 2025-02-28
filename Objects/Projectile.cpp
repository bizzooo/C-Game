//
// Created by VidBe on 27/02/2025.
//

#include "Projectile.h"

#include <cmath>

Projectile::Projectile(const std::string &textureFile, int textureRectSize, float hitBoxSizeX,
                       float hitBoxSizeY, float hBOriginX, float hBOriginY, const GameObject& gameObject):
    GameObject(),
    hitBox(new HitBox(hitBoxSizeX,hitBoxSizeY,hBOriginX,hBOriginY,this)),
    angle(atan2(sf::Mouse::getPosition().y - gameObject.getSprite().getPosition().y,sf::Mouse::getPosition().x - gameObject.getSprite().getPosition().x))
{
    texture = sf::Texture(textureFile);
    textureRectScale = textureRectSize;
    sprite = sf::Sprite(texture);
    spriteRow = 0;
    spriteCol = 0;
    spriteTimer = 0;
}

void Projectile::update(float deltaTime) {
    updateHitBox();
    animateObject();
}
