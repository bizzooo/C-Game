//
// Created by VidBe on 23/02/2025.
//

#include "GameEngine.h"

#include "Global.h"
#include "Objects/Player.h"

GameEngine::GameEngine():
window(sf::VideoMode({1920,1080}),"RPG Game"),
view(sf::FloatRect({200.f, 200.f},{1920,1080}))
{
    window.setFramerateLimit(144);
    objectManager = std::make_unique<ObjectManager>();
    objectManager->addObject(std::make_unique<Player>(1,"SampleAnimation.png", 10, 10));
    objectManager->addObject(std::make_unique<GameObject>(2,"firePit.png",64,5,5,128.f,64.f,64,64));
    tileMap = std::make_unique<TileMap>("MapData/sheet.png", "MapData/Map.txt", sf::Vector2u(tileSize, tileSize), scale);
}

// TODO WHERE EVERYTHING HAPPENS
void GameEngine::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asMilliseconds();
        update(deltaTime);
        render();
    }
}

void GameEngine::processEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is <sf::Event::Closed>())
            window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::T)
                debugMode = !debugMode;
        }
    }
}

void GameEngine::update(float deltaTime) {
    objectManager->updateAll(deltaTime);

    view.setCenter(objectManager->getPlayerPosition());
    window.setView(view);
}

void GameEngine::renderDebugText() {

    sf::Text text(font);
    text.setCharacterSize(15);
    std::pmr::vector<std::string> debugTexts;
    debugTexts.push_back("World X:" + std::to_string(objectManager->getPlayerPosition().x));
    debugTexts.push_back("World Y:" + std::to_string(objectManager->getPlayerPosition().y));
    debugTexts.push_back("World COL: " + std::to_string(static_cast<int>(objectManager->getPlayerPosition().x/scaledSize)));
    debugTexts.push_back("World ROW: " + std::to_string(static_cast<int>(objectManager->getPlayerPosition().y/scaledSize)));
    debugTexts.push_back("Sprite Timer: " + std::to_string(objectManager->getPlayer()->spriteTimer));
    debugTexts.push_back("Sprite COL: " + std::to_string(objectManager->getPlayer()->spriteCol));
    debugTexts.push_back("Sprite ROW: " + std::to_string(objectManager->getPlayer()->spriteRow));
    debugTexts.push_back("IDLE: " + std::to_string(objectManager->getPlayer()->idle));
    debugTexts.push_back("ATTACKING: " + std::to_string(objectManager->getPlayer()->attacking));
    debugTexts.push_back("firePit Y" + std::to_string(objectManager->getObjectById(2)->getWorldY()));

    window.setView(window.getDefaultView());

    for (int i = 0; i < debugTexts.size(); i++) {
        text.setString(debugTexts[i]);
        text.setPosition({0,static_cast<float>(i*16)});
        window.draw(text);
    }
    window.setView(view);
}

void GameEngine::render() {
    window.clear(sf::Color::Black);

    window.draw(*tileMap);

    objectManager->drawAll(window);

    if (debugMode) {
        renderDebugText();
    }

    window.display();
}
