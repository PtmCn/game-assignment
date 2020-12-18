#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Hitbox.hpp"

class Entity : public sf::Sprite{
    public:
        sf::Vector2f velocity ,size , frameSize , framesAmount;
        std::vector<sf::IntRect> frames;
        Hitbox hitbox;

};
