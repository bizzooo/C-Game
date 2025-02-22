//
// Created by VidBe on 15/02/2025.
//

#include "Player.h"

#include <iostream>

#include "Global.h"
#include <SFML/Graphics.hpp>

constexpr int spSize = 64;
int spriteRow = 0;
sf::Vector2 spriteSize = {64,64};

Player::Player(const sf::Texture &pTexture):
health(100),
spriteColumn(0),
spriteTimer(0),
isMoving(false),
attacking(false),
animationComplete(true),
speed(0.5f),
direction(DOWN),
playerSprite(pTexture)
{
    this->playerSprite->setTextureRect(sf::IntRect({0, 0}, {32, 32}));
    this->playerSprite->scale({3.0f,3.0f});
    this->playerSprite->setOrigin({32.f, 48.f});
    this->hitBox.setSize({16*3,32*3});
    this->hitBox.setOrigin({48.f, 48.f});
    this->hitBox.setPosition(playerSprite->getPosition());
    this->hitBox.setOutlineThickness(1.f);
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::Red);
}

void Player::move(float deltaTime) {
    if (isKeyPressed(sf::Keyboard::Key::W)) {
        const sf::Vector2f position = playerSprite->getPosition();
        if (isKeyPressed(sf::Keyboard::Key::A)) {
            direction = LEFT_UP;
            spriteRow = 7;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(-speed*deltaTime/1.5f,-speed*deltaTime/1.5f));
        } else if (isKeyPressed(sf::Keyboard::Key::D)) {
            direction = RIGHT_UP;
            spriteRow = 1;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(speed*deltaTime/1.5f,-speed*deltaTime/1.5f));
        } else {
            direction = UP;
            spriteRow = 0; // UP
            isMoving = true;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(0,-speed*deltaTime));
        }
    } else if (isKeyPressed(sf::Keyboard::Key::S)) {
        const sf::Vector2f position = playerSprite->getPosition();
        if (isKeyPressed(sf::Keyboard::Key::A)) {
            direction = LEFT_DOWN;
            spriteRow = 5;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(-speed*deltaTime/1.5f,speed*deltaTime/1.5f));
        } else if (isKeyPressed(sf::Keyboard::Key::D)) {
            direction = RIGHT_DOWN;
            spriteRow = 3;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(speed*deltaTime/1.5f,speed*deltaTime/1.5f));
        } else {
            direction = DOWN;
            spriteRow = 4;
            isMoving = true;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(0,speed*deltaTime));
        }
    }else if (isKeyPressed(sf::Keyboard::Key::A)) {
        const sf::Vector2f position = playerSprite->getPosition();
        direction = LEFT;
        spriteRow = 6;
        isMoving = true;
        playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
        playerSprite->setPosition(position + sf::Vector2f(-speed*deltaTime,0));
    }else if (isKeyPressed(sf::Keyboard::Key::D)) {
        const sf::Vector2f position = playerSprite->getPosition();
        if (isKeyPressed(sf::Keyboard::Key::Space)) {
            isMoving = true;
            spriteRow = 16;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(speed*deltaTime,0));
        } else {
            direction = RIGHT;
            spriteRow = 2;
            isMoving = true;
            playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
            playerSprite->setPosition(position + sf::Vector2f(speed*deltaTime,0));
        }
    }

    if (!isKeyPressed(sf::Keyboard::Key::W) && !isKeyPressed(sf::Keyboard::Key::A) && !isKeyPressed(sf::Keyboard::Key::S) && !isKeyPressed(sf::Keyboard::Key::D)) {
        isMoving=false;
    }
    hitBox.setPosition({playerSprite->getPosition().x + 24,playerSprite->getPosition().y});
}

void Player::attack() {
    animatePlayer(15,6);
    switch (direction) {
        case RIGHT:
            spriteRow = 16;
    }
    playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
}

void Player::animatePlayer(const int spriteTimerReset, const int spriteColumnReset) {
    spriteTimer++;
    if (spriteTimer >= spriteTimerReset) {
        spriteColumn++;
        spriteTimer = 0;
    }
    if (spriteColumn >= spriteColumnReset) {
        spriteColumn = 0;
    }
}

void Player::update(float deltaTime) {
    attacking = isKeyPressed(sf::Keyboard::Key::Space);
    if (attacking) {
        attack();
    }
    if (isMoving && !attacking) {
        animatePlayer(20,6);
    } else if (!attacking){
        animatePlayer(20,8);
        switch(direction) {
            case UP:
                spriteRow = 8;
            break;
            case RIGHT_UP:
                spriteRow = 9;
            break;
            case RIGHT:
                spriteRow = 10;
            break;
            case RIGHT_DOWN:
                spriteRow = 11;
            break;
            case DOWN:
                spriteRow = 12;
            break;
            case LEFT_DOWN:
                spriteRow = 13;
            break;
            case LEFT:
                spriteRow = 14;
            break;
            case LEFT_UP:
                spriteRow = 15;
            break;
        }
        playerSprite->setTextureRect(sf::IntRect({spriteColumn*spSize,spriteRow*spSize},spriteSize));
    }
    move(deltaTime);
    if (debugMode) {
        std::cout << "SPRITE COL: " << spriteColumn << std::endl;
        std::cout << "SPRITE ROW: " << spriteRow << std::endl;
        std::cout << "TIMER: " << spriteTimer << std::endl;
        std::cout << "Attacking: " << attacking << std::endl;
        std::cout << "isMoving: " << isMoving << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}


