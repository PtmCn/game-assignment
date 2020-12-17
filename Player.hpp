#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Hitbox.hpp"

#include "../include/Entity.hpp"

class Player : public Entity{
private:
    float speed;

public:
    Player (float X, float Y, float W, float H);
    void update(bool &W, bool &A, bool &S, bool &D, float &deltaTime);
};
