#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <SFML/Graphics.hpp>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap(const std::string& tileset, const std::string& mapFile, sf::Vector2u tileSize, float scale);
    bool load();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray vertices;
    sf::Texture tilesetTexture;
    std::string tilesetPath;
    std::string mapFilePath;
    sf::Vector2u tileSize;
    float scale;
};

#endif // TILE_MAP_H
