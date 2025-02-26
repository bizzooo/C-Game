//
// Created by VidBe on 16/02/2025.
//

#ifndef GLOBAL_H
#define GLOBAL_H

const sf::Font font("dogica.ttf");
constexpr int tileSize = 16;
constexpr float scale = 3.f;
constexpr int scaledSize = tileSize*scale;
inline bool debugMode = false;

enum class Direction {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight,
    None
};

#endif //GLOBAL_H
