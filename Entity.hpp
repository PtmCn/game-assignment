#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Hitbox.hpp"

class Entity : public sf::Drawable, public sf::Transformable{
    private:
//        Entity::draw(sf::RenderTarget target, sf::RenderStates states)const;
    public:
        sf::VertexArray vertices;
        sf::Texture texture;
        sf::Vector2f velocity;
        float x,y,w,h;
        hitBox hitbox;

        void setTexture(const char* tex);

};
