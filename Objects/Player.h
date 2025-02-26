//
// Created by VidBe on 15/02/2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    Direction currentDirection = Direction::Down;
    bool attacking = false;
    bool idle = true;
    bool attackAnimationFlag = false;
    int attackAnimationCounter = 0;

    Player(int id, const std::string& textureFile, int col, int row);

    void idleAnimation();

    void attackAnimation();

    void moveAnimation();

    void animatePlayer();

    void updateDirection(const sf::Vector2f &movement);

    void update(float deltaTime) override;

    void handleCollision(GameObject *A);

    // Additional player-specific methods (e.g., attack, move) can be added here.
};

#endif // PLAYER_H