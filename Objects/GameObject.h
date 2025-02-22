//
// Created by VidBe on 22/02/2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/Graphics.hpp"


class GameObject {
public:
    sf::Texture objectTexture;
    sf::Sprite objectSprite;

    explicit GameObject(const sf::Texture &objTexture,const int textureRectSize): objectSprite(objTexture) {
        objectSprite.setTextureRect(sf::IntRect({0,0},{textureRectSize,textureRectSize}));
    }

};



#endif //GAMEOBJECT_H
