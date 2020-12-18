#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Platform.hpp"
#include "../include/Entity.hpp"

class Player : public Entity{
private:
    bool collision;
    bool onGround;
    float speed;
    float jumpHeight;

    int walkCount,idleCount, walkFrames, idleFrames,walkSpeed,idleSpeed;

public:
    Player (float X, float Y, float W, float H, sf::Texture& t);
    void update(bool &W, bool &A, bool &S, bool &D,std::vector<Platform>& level);
    void collide(float xvel, float yvel ,std::vector<Platform>& level);
    void animate();
    void walk();
    void idle();

};
