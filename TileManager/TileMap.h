//
// Created by VidBe on 16/02/2025.
//

#ifndef TILEMAP_H
#define TILEMAP_H


#include <filesystem>
#include <fstream>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class TileMap : public sf::Drawable, public sf::Transformable{
public:
    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;

    explicit TileMap(const std::filesystem::path& tilesetFile,const std::string &mapFile,sf::Vector2u tileSize, const float scale){
        // Load the tileset texture.
        if (!m_tileset.loadFromFile(tilesetFile.string())) {
            std::cerr << "Error: Could not open texture file: " << mapFile << std::endl;
            return;
        }
        m_tileset.setSmooth(false);

        // Open the map file.
        std::ifstream file(mapFile);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open map file: " << mapFile << std::endl;
            return;;
        }

        // Read header lines: assuming your file has these 4 header lines.
        int tilesWide = 0, tilesHigh = 0, tileWidth = 0, tileHeight = 0;
        for (int i = 0; i < 4; ++i) {
            std::string line;
            if (!std::getline(file, line))
                break;
            std::istringstream iss(line);
            std::string key;
            int value;
            if (iss >> key >> value) {
                if (key == "tileswide")
                    tilesWide = value;
                else if (key == "tileshigh")
                    tilesHigh = value;
                else if (key == "tilewidth")
                    tileWidth = value; // usually same as tileSize.x
                else if (key == "tileheight")
                    tileHeight = value; // usually same as tileSize.y
            }
        }

        // Skip lines until "layer" is found.
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("layer") == 0)
                break;
        }

        // Resize the vertex array to fit the whole map (6 vertices per tile).
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(tilesWide * tilesHigh * 6);

        // Fill the vertex array.
        for (int j = 0; j < tilesHigh; ++j) {
            std::getline(file, line);
            std::istringstream ss(line);
            for (int i = 0; i < tilesWide; ++i) {
                std::string token;
                if (!std::getline(ss, token, ','))
                    break;
                int tileNumber = std::stoi(token);

                // Calculate texture coordinates in the tileset.
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // Get a pointer to the current tile's vertices in the vertex array.
                sf::Vertex* quad = &m_vertices[(i + j * tilesWide) * 6];

                // Define the 6 vertices for the two triangles.
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                quad[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                // Set the corresponding texture coordinates.
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                quad[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
        this->setScale({scale,scale});
    }


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // Apply the transform.
        states.transform *= getTransform();

        // Set the tileset texture.
        states.texture = &m_tileset;

        // Draw the vertex array in one call.
        target.draw(m_vertices, states);
    }
};

#endif // TILEMAP_H

