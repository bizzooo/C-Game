//
// Created by VidBe on 23/02/2025.
//

#include "ObjectManager.h"
#include "../Objects/Player.h"
#include <algorithm>

void ObjectManager::addObject(std::unique_ptr<GameObject> obj) {
    gameObjects.push_back(std::move(obj));
}

void ObjectManager::updateAll(float deltaTime) {
    for (auto& obj : gameObjects) {
        obj->update(deltaTime);
    }
}

void ObjectManager::drawAll(sf::RenderWindow &window) {
    // Sort objects by their y-coordinate (for layering)
    std::sort(gameObjects.begin(), gameObjects.end(),
        [](const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b) {
            return a->getWorldY() < b->getWorldY();
        });
    for (const auto& obj : gameObjects) {
        window.draw(obj->getSprite());
        if (debugMode) {
            window.draw(obj->ySortOrigin);
            window.draw(obj->hitBox->shape);
        }
    }
}

sf::Vector2f ObjectManager::getPlayerPosition() const {
    // Assuming the first player added is the one to follow:
    for (const auto& obj : gameObjects) {
        if (dynamic_cast<Player*>(obj.get())) {
            return obj->getPosition();
        }
    }
    return sf::Vector2f(0.f, 0.f);
}

Player* ObjectManager::getPlayer() {
    for (const auto& obj : gameObjects) {
        if (auto player = dynamic_cast<Player*>(obj.get())) {
            return player;
        }
    }
    return nullptr;
}

GameObject* ObjectManager::getObjectById(int id) {
    for (const auto& obj : gameObjects) {
        if (obj->id == id)
            return obj.get();
    }
    return nullptr;
}
