//
// Created by VidBe on 15/02/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>




class Player {
    enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        LEFT_DOWN,
        LEFT_UP,
        RIGHT_DOWN,
        RIGHT_UP
    };

public:
    int health;
    int spriteColumn;
    int spriteTimer;
    bool isMoving;
    bool animationComplete;
    bool attacking;
    float speed;
    Direction direction;
    std::optional<sf::Sprite> playerSprite;
    sf::RectangleShape hitBox;


    Player(const sf::Texture &pTexture);

    void move(float deltaTime);

    void attack();

    void animatePlayer(int spriteTimerReset, int spriteColumnReset);

    void update(float deltaTime);
};



#endif //PLAYER_H
