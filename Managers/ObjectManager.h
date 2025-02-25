//
// Created by VidBe on 23/02/2025.
//

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../Objects/GameObject.h"
#include "../Objects/Player.h"

class ObjectManager {
public:
    void addObject(std::unique_ptr<GameObject> obj);
    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow &window);

    // Returns the player's position for camera centering.
    sf::Vector2f getPlayerPosition() const;

    Player* getPlayer();

    GameObject *getObjectById(int id);

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};

#endif // OBJECT_MANAGER_H
