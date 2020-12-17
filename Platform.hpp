#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Entity.hpp"

class Platform : public Entity{
public:
    Platform ();
    void init(float X, float Y, float W, float H);
};

