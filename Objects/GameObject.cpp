//
// Created by VidBe on 23/02/2025.
//

#include "GameObject.h"

GameObject::GameObject(const int id,const std::string& textureFile, int textureRectSize, int col, int row):
id(id),
texture(textureFile),
textureRectScale(textureRectSize),
sprite(texture),
spriteCol(0),
spriteTimer(0),
spriteRow(0)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {textureRectSize, textureRectSize}));
    sprite.scale({scale,scale});
    sprite.setPosition({static_cast<float>(col*scaledSize),static_cast<float>(row*scaledSize)});
    sprite.setOrigin({static_cast<float>(textureRectSize/2), static_cast<float>(textureRectSize)});
    ySortOrigin.setRadius(5.f);
    ySortOrigin.setFillColor(sf::Color::Red);
    ySortOrigin.setOrigin({5.f, 5.f});
    ySortOrigin.setPosition(getPosition());
}

GameObject::GameObject(const int id,const std::string& textureFile, int textureRectSize, int col, int row, float hitBoxSizeX, float hitBoxSizeY,float hBOriginX, float hBOriginY):
id(id),
texture(textureFile),
textureRectScale(textureRectSize),
sprite(texture),
spriteCol(0),
spriteTimer(0),
spriteRow(0)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {textureRectSize, textureRectSize}));
    sprite.scale({scale,scale});
    sprite.setPosition({static_cast<float>(col*scaledSize),static_cast<float>(row*scaledSize)});
    sprite.setOrigin({static_cast<float>(textureRectSize/2), static_cast<float>(textureRectSize)});
    ySortOrigin.setRadius(5.f);
    ySortOrigin.setFillColor(sf::Color::Red);
    ySortOrigin.setOrigin({5.f, 5.f});
    ySortOrigin.setPosition(getPosition());
    hitBoxShape.setSize({hitBoxSizeX,hitBoxSizeY});
    hitBoxShape.setOrigin({hBOriginX,hBOriginY});
    hitBoxShape.setPosition(sprite.getPosition());
    hitBoxShape.setFillColor(sf::Color::Transparent);
    hitBoxShape.setOutlineThickness(1.f);
    hitBoxShape.setOutlineColor(sf::Color::Red);
    hitBox = hitBoxShape.getGlobalBounds();
}

void GameObject::animateObject() {
    spriteTimer++;
    if (spriteTimer >= 15) {
        spriteCol++;
        spriteTimer = 0;
    }
    if (spriteCol >= 12) {
        spriteCol = 0;
    }

    sprite.setTextureRect(sf::IntRect({spriteCol*64,spriteRow*64},{64,64}));
}

void GameObject::updateHitBox() {
    hitBoxShape.setPosition(sprite.getPosition());
    hitBox = hitBoxShape.getGlobalBounds();
}

void GameObject::setPosition(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
    ySortOrigin.setPosition(pos);
    updateHitBox();
}

void GameObject::handleCollision(GameObject *a) {

}

void GameObject::update(float deltaTime) {
    animateObject();
}

void GameObject::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

const sf::Sprite& GameObject::getSprite() const {
    return sprite;
}

sf::Vector2f GameObject::getPosition() const {
    return sprite.getPosition();
}

float GameObject::getWorldY() const {
    return sprite.getPosition().y;
}