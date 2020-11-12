#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable{
    private:
        void draw(sf::RenderTarget target, sf:: Renderstates states)const;
    public:
        sf::VertexArray m_vertices;
        sf::Texture m_texture;
        sfTransform m_transform;

};


