#include <SFML/Graphics.hpp>
#include "./include/Entity.hpp"
#include "./include/Platform.hpp"

 Platform::Platform(float X,float Y,float W,float H,sf::Texture& t){

    size.x = W;
    size.y = H;


    hitbox.left = X + 0.f;
    hitbox.right = X + size.x + 9.f;
    hitbox.top = Y + 0.f;
    hitbox.bottom = Y + size.y - 0.f;

    setTexture(t);
    setPosition(X,Y);
}
