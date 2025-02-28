#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "HitBox.h"
#include "../Global.h"

class HitBox;

enum class Direction;

class GameObject {
public:
    std::optional<const int> id;
    int spriteRow;
    int spriteCol;
    int spriteTimer;
    float speed;
    sf::CircleShape ySortOrigin;
    HitBox* hitBox;

    GameObject();

    GameObject(int id, const std::string &textureFile, int textureRectSize, int col, int row, float hitBoxSizeX,
               float hitBoxSizeY, float hBOriginX, float hBOriginY);

    GameObject(const std::string &textureFile, int textureRectSize);

    virtual void animateObject();

    virtual void updateHitBox();

    virtual ~GameObject() = default;

    virtual void setPosition(const sf::Vector2f& pos);

    virtual void handleCollision(GameObject *a);


    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow &window);

    // Getters for rendering order and position
    const sf::Sprite& getSprite() const;
    sf::Vector2f getPosition() const;
    float getWorldY() const;
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    int textureRectScale;
};

#endif // GAME_OBJECT_H