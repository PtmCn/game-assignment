#include <SFML/Graphics.hpp>
#include "./include/Entity.hpp"
#include "./include/Player.hpp"

Player::Player(float X,float Y,float W,float H){\
    speed = 100.f;
    x = X;
    y = Y;
    w = W;
    h = H;
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(4);

    vertices[0].position = sf::Vector2f(0,0);
    vertices[1].position = sf::Vector2f(W,0);
    vertices[2].position = sf::Vector2f(W,H);
    vertices[3].position = sf::Vector2f(0,H);

    vertices[0].texCoords = sf::Vector2f(0,0);
    vertices[1].texCoords = sf::Vector2f(W,0);
    vertices[2].texCoords = sf::Vector2f(W,H);
    vertices[3].texCoords = sf::Vector2f(0,H);
}

void Player::update(bool &W, bool &A, bool &S, bool &D, float &deltaTime){
    //player controls
    if(W) velocity.y = -1.f;
    if(A) velocity.x = -1.f;
    if(S) velocity.y = 1.f;
    if(D) velocity.x = 1.f;
    if(!(A||D)) velocity.x = 0;
    if(!(W||S)) velocity.y = 0;

    x += velocity.x * speed * deltaTime;
    y += velocity.y * speed * deltaTime;

    setPosition(x,y);
}
