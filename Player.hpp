#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Entity.hpp"

class Player : public Entity{
private:
    float m_xvel;
    float m_yvel;
public:
    Player (const std::string& textureFile, float i_x ,float i_y,float i_w,float i_h);
};
