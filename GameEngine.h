//
// Created by VidBe on 23/02/2025.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Managers/ObjectManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "TileManager/TileMap.h"


class GameEngine {
public:
    GameEngine();
    void run();
private:
    sf::RenderWindow window;
    sf::View view;
    sf::Clock clock;

    //Game Systems
    std::unique_ptr<ObjectManager> objectManager;
    std::unique_ptr<TileMap> tileMap;

    //Game logic
    void processEvents();
    void update(float deltaTime);

    void renderDebugText();

    void render();
};



#endif //GAMEENGINE_H
