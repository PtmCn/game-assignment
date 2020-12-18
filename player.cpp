#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "./include/Entity.hpp"
#include "./include/Player.hpp"
#include "./include/Platform.hpp"

float accelGravity = 0.2f;
float maxGravity = 5.f;

Player::Player(float X,float Y,float W,float H,sf::Texture& t)
{
    speed = 2.f;
    jumpHeight = 5.f;

    size.x = W;
    size.y = H;

    walkCount = 0;
    idleCount = 0;

    walkFrames = 12;
    idleFrames = 12;

    walkSpeed = 4;
    idleSpeed = 7;

    frameSize.x = 32;
    frameSize.y = 32;

    framesAmount.x = t.getSize().x/frameSize.x;
    framesAmount.y = t.getSize().y/frameSize.y;

    for(int y = 0; y < framesAmount.y; y++){
        for(int x = 0;x < framesAmount.x;x++){
            sf::IntRect frame(x * frameSize.x,y * frameSize.y,frameSize.x,frameSize.y);
            frames.push_back(frame);
        }
    }
    setTextureRect(frames[0]);
    setTexture(t);
    setPosition(X,Y);
}

void Player::update(bool &W, bool &A, bool &S, bool &D,std::vector<Platform>& level){
    //player controls
    std::cout << onGround << std::endl;

    if(W && onGround) velocity.y = jumpHeight * -1;

    if(onGround == false){
            velocity.y += accelGravity;
            if(velocity.y > maxGravity)velocity.y = maxGravity;
    }

    if(A)velocity.x = -1.f;
    if(S) velocity.y = 1.f;
    if(D) velocity.x = 1.f;
    if(!(A||D)) velocity.x = 0;
    if(!(W||S)) velocity.y = 0;

    move(velocity.x * speed , 0);
    collide(velocity.x,0,level);

    onGround = false;
    move(0, velocity.y);
    collide(0,velocity.y,level);
    animate();
}

void Player::collide(float xvel, float yvel,std::vector<Platform>& level)
{
    for(Platform& p : level){
        if(getPosition().x + 13.f < p.hitbox.right &&
           getPosition().x + size.x -4.f> p.hitbox.left &&
           getPosition().y < p.hitbox.bottom &&
           getPosition().y + size.y > p.hitbox.top){
                collision =  true;
           }
           else{
            collision =  false;
           }
           if(collision){
                if(xvel > 0){
                    setPosition(p.hitbox.left - size.x + 4.f,getPosition().y);
                    velocity.x = 0.f;
                }
                if(xvel < 0){
                    setPosition(p.hitbox.right - 15.f,getPosition().y);
                    velocity.x = 0.f;
                }
                if(yvel > 0){
                    setPosition(getPosition().x, p.hitbox.top - size.y + 0.f);
                    velocity.y = 0.f;
                    onGround = true;
                }
                if(yvel < 0){
                    setPosition(getPosition().x ,p.hitbox.bottom - 0.f);
                    velocity.y = 0.f;
                }
           }

    }
}

void Player::animate()
{
    if(abs(velocity.x) > 0)
        walk();
    else
        idle();
}

void Player::walk()
{
    for(int i = 0; i < walkFrames;i++)
        if(walkCount == (i+1) * walkSpeed)
            setTextureRect(frames[i]);
    if(walkCount == walkFrames * walkSpeed)
        walkCount = 0;
    walkCount++;
}

void Player::idle()
{
    for(int i = 1; i < idleFrames;i++)
        if(idleCount == (i+1) * idleSpeed)
            setTextureRect(frames[i+walkFrames]);
    if(idleCount == idleFrames * idleSpeed)
        idleCount = 0;
    idleCount++;
}
