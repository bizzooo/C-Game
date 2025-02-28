//
// Created by VidBe on 23/02/2025.
//

#include "Player.h"

#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include "../Global.h"

Player::Player(const int id,const std::string& textureFile, int col, int row)
    : GameObject(id, textureFile, 32, col,row,scaledSize,32*scale,scaledSize/2,scaledSize*2)
{
    spriteCol = 0;
    spriteRow = 0;
    spriteTimer = 0;
    currentDirection = Direction::Down;
    speed = 0.5f;
    sprite.setScale({3.f, 3.f});
    sprite.setOrigin({32.f, 48.f});
    sprite.setOrigin({static_cast<float>(64/2), static_cast<float>(64)});
}

void Player::idleAnimation() {
    switch (currentDirection) {
        case Direction::Up:       spriteRow = 8; break;
        case Direction::UpRight:  spriteRow = 9; break;
        case Direction::Right:    spriteRow = 10; break;
        case Direction::DownRight:spriteRow = 11; break;
        case Direction::Down:     spriteRow = 12; break;
        case Direction::DownLeft: spriteRow = 13; break;
        case Direction::Left:     spriteRow = 14; break;
        case Direction::UpLeft:   spriteRow = 15; break;
        default: break;
    }
    spriteTimer++;
    if (spriteTimer >= 20) {
        spriteCol++;
        spriteTimer = 0;
    }
    if (spriteCol >= 8) {
        spriteCol = 0;
    }
}

void Player::attackAnimation() {
    switch (currentDirection) {
        //case Direction::Up:       spriteRow = 0; break;
        //case Direction::UpRight:  spriteRow = 1; break;
        case Direction::Right:    spriteRow = 16; break;         //TODO FINISH ATTACK SPRITES
        //case Direction::DownRight:spriteRow = 3; break;
        //case Direction::Down:     spriteRow = 4; break;
        //case Direction::DownLeft: spriteRow = 5; break;
        //case Direction::Left:     spriteRow = 6; break;
        //case Direction::UpLeft:   spriteRow = 7; break;
        default: break;
    }
    attackAnimationFlag = true;
    spriteTimer++;
    if (spriteTimer >= 20) {
        if (spriteCol == 5 && spriteTimer >= 40) {
            spriteCol++;
            spriteTimer = 0;
        }
        spriteCol++;
        spriteTimer = 0;
    }
    if (spriteCol >= 6) {
        spriteCol = 0;
        attackAnimationCounter++;
        if (attackAnimationCounter >= 2) {
            attackAnimationFlag = false;
            attackAnimationCounter = 0;
        }
    }
    if (!attackAnimationFlag) {
        attacking = false;
    }
}

void Player::moveAnimation() {
    switch (currentDirection) {
        case Direction::Up:       spriteRow = 0; break;
        case Direction::UpRight:  spriteRow = 1; break;
        case Direction::Right:    spriteRow = 2; break;
        case Direction::DownRight:spriteRow = 3; break;
        case Direction::Down:     spriteRow = 4; break;
        case Direction::DownLeft: spriteRow = 5; break;
        case Direction::Left:     spriteRow = 6; break;
        case Direction::UpLeft:   spriteRow = 7; break;
        default: break;
    }
    spriteTimer++;
    if (spriteTimer >= 20) {
        spriteCol++;
        spriteTimer = 0;
    }
    if (spriteCol >= 6) {
        spriteCol = 0;
    }
}

void Player::animatePlayer() {
    if (attacking) {
        attackAnimation();
    } else if (idle) {
        idleAnimation();
    } else {
        moveAnimation();
    }
    sprite.setTextureRect(sf::IntRect({spriteCol*64,spriteRow*64},{64,64}));
}

void Player::updateDirection(const sf::Vector2f& movement) {
    if (movement.x == 0.f && movement.y == 0.f) {
        return;
    }

    // Determine primary direction based on sign of movement
    if (movement.y < 0.f) { // moving up
        if (movement.x < 0.f)
            currentDirection = Direction::UpLeft;
        else if (movement.x > 0.f)
            currentDirection = Direction::UpRight;
        else
            currentDirection = Direction::Up;
    } else if (movement.y > 0.f) { // moving down
        if (movement.x < 0.f)
            currentDirection = Direction::DownLeft;
        else if (movement.x > 0.f)
            currentDirection = Direction::DownRight;
        else
            currentDirection = Direction::Down;
    } else { // purely horizontal movement
        if (movement.x < 0.f)
            currentDirection = Direction::Left;
        else if (movement.x > 0.f)
            currentDirection = Direction::Right;
    }
    // Map the direction to a sprite row (this mapping depends on your sprite sheet)
}


void Player::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= 1.f;
    if (isKeyPressed(sf::Keyboard::Key::S))
        movement.y += 1.f;
    if (isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= 1.f;
    if (isKeyPressed(sf::Keyboard::Key::D))
        movement.x += 1.f;

    // Normalize the vector if necessary (to avoid faster diagonal movement)
    if (movement.x != 0.f || movement.y != 0.f) {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= length;  // Now movement has a length of 1
        movement *= speed;   // Multiply by speed to get the desired velocity
    }
    if (isKeyPressed(sf::Keyboard::Key::Space)) {
        attacking = true;
        if (!attackAnimationFlag) {
            spriteCol = 0;
        }
    }
    idle = (movement.x == 0.f && movement.y == 0.f);
    updateDirection(movement);
    animatePlayer();
    ySortOrigin.move(movement * deltaTime);
    sprite.move(movement * deltaTime);
    updateHitBox();
}

void Player::handleCollision(GameObject* A) {
    if (hitBox->value.findIntersection(A->hitBox->value)) {
        sf::FloatRect intersection = hitBox->value.findIntersection(A->hitBox->value).value();
        sf::Vector2f mtv(0.f,0.f);

        if (intersection.size.x < intersection.size.y) {
            if (hitBox->value.position.x < A->hitBox->value.position.x) {
                mtv.x = -intersection.size.x;
            } else {
                mtv.x = intersection.size.x;
            }
        } else {
            if (hitBox->value.position.y < A->hitBox->value.position.y) {
                mtv.y = -intersection.size.y;
            } else {
                mtv.y = intersection.size.y;
            }
        }
        sprite.move(mtv);
    }
}
