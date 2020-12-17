#include <SFML/Graphics.hpp>
#include "include/Entity.hpp"

void Entity::draw(sf::RenderTarget& target, sf:: Renderstates states)const{
    states.transform *= getTransform();

    states.texture = &texture;

    target.draw(vertices, states);
}

void Entity::setTexture(const char* tex){
    texture.loadFromFile(tex);
}
