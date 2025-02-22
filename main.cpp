#include <iostream>
#include <SFMl/Graphics.hpp>

#include "Global.h"
#include "Player.h"
#include "TileManager/TileMap.h"
#include <fstream>
#include <string>
#include <vector>

#include "Objects/GameObject.h"
#include "Objects/FirePit.h"

sf::Vector2u resolution(1920,1080);

void updateWindow(sf::RenderWindow& window) {
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

int main() {
   //INIT
   sf::Font font("dogica.ttf");
   sf::Text text(font);
   text.setString("Hello world");
   text.setCharacterSize(24);
   sf::RenderWindow window(sf::VideoMode(resolution), "RPG Game");
   sf::View view(sf::FloatRect({200.f, 200.f}, {static_cast<float>(resolution.x), static_cast<float>(resolution.y)}));
   window.setFramerateLimit(144);
   sf::Texture playerTexture("SampleAnimation.png");
   Player player(playerTexture);
   int spriteTimer = 0;

   sf::Texture firePitTexture("firePit.png");
   FirePit firePit(firePitTexture,64);


   TileMap tileMap("MapData/sheet.png","MapData/Map.txt",{16,16},3.f);

   sf::Clock clock;
   while (window.isOpen()) {
      updateWindow(window);

      view.setCenter({player.playerSprite->getPosition().x,player.playerSprite->getPosition().y});
      window.setView(view);
      if (window.hasFocus()) {
         float deltaTime = clock.restart().asMilliseconds();

         player.update(deltaTime);


         window.clear(sf::Color::Black);
         window.draw(tileMap);
         window.draw(text);
         window.draw(firePit.getSprite());
         firePit.animateSprite(15,12);

         if (player.playerSprite.has_value()) {
            window.draw(*player.playerSprite);
         }
         if (debugMode) {
            window.draw(player.hitBox);
         }
         window.display();
      }
   }
   return 0;
}