#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

const int windowWidth = 1260;
const int windowHeight = 720;
const int halfWinWidth = windowWidth/2;
const int halfWinHeight = windowHeight/2;

using namespace std;

class platformClass{
    public:
        float xpos;
        float ypos;
        float xvel;
        float yvel;
        int scale;
        float topside;
        float bottomside;
        float rightside;
        float leftside;
        sf::Sprite image;
        platformClass(int initxpos,int initypos,sf::Sprite sprite){
            scale = 5;
            image = sprite;
            image.setPosition(initxpos,initypos);
            image.setScale(scale,scale);
            leftside = image.getPosition().x;
            rightside = image.getPosition().x + (image.getLocalBounds().width * scale);
            topside = image.getPosition().y;
            bottomside = image.getPosition().y + (image.getLocalBounds().height *scale);
        }
};

class playerClass{
    public:
        bool playerFaceRight;
        bool onGround;
        bool iscollide;
        float xpos;
        float ypos;
        float xvel;
        float yvel;
        int scale;
        sf::Sprite image;
        playerClass(sf::Sprite sprite){
            image = sprite;
            playerFaceRight = true;
            xpos = 0;
            ypos = 0;
            xvel = 0;
            yvel = 0;
            scale = 1;
            onGround = false;
            iscollide = false;


        }
        void update(bool keyUp,bool keyDown,bool keyRight,bool keyLeft,platformClass level[5],float deltatime){
           if (keyRight){
                playerFaceRight = true;
                xvel = 200;
           }
           if (keyLeft){
                playerFaceRight = false;
                xvel = -200;
           }
           if (keyUp){
                yvel = -200;
           }
           if (keyDown){
                yvel = 200;
           }
           if (!(keyRight || keyLeft))
           {
                xvel = 0 ;
           }
           if (onGround == true){
             yvel = 0;
           }
            image.move(sf::Vector2f(xvel * deltatime,0));
            collide(xvel,0,level);
            image.move(sf::Vector2f(0,yvel * deltatime));
            collide(0,yvel,level);
        }
        void collide(float xveldelta,float yveldelta,platformClass level[5]){
            for(int i = 0;i<5;i++){
                if(image.getPosition().x + (image.getLocalBounds().width * scale)> level[i].leftside &&
                    image.getPosition().x < level[i].rightside &&
                    image.getPosition().y + (image.getLocalBounds().height *scale)> level[i].topside &&
                    image.getPosition().y < level[i].bottomside){
                    iscollide = true;
                }
                else{
                    iscollide = false;
                }
                if(iscollide){
                    if(xveldelta > 0){
                        image.setPosition(sf::Vector2f(level[i].leftside - image.getLocalBounds().width * scale,image.getPosition().y));
                    }
                    if(xveldelta < 0){
                        image.setPosition(sf::Vector2f(level[i].rightside,image.getPosition().y));
                    }
                    if(yveldelta > 0){
                        image.setPosition(sf::Vector2f(image.getPosition().x,level[i].topside - image.getLocalBounds().height * scale));
                    }
                    if(yveldelta < 0){
                        image.setPosition(sf::Vector2f(image.getPosition().x,level[i].bottomside));
                    }
                }
            }
        }
};

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game");

    bool keyUp, keyDown, keyLeft, keyRight = false;

    sf::Font minecraftfont;
    minecraftfont.loadFromFile("data/fonts/Minecraft.ttf");

    sf::Text helloText("Hello World!",minecraftfont,50);

    sf::Texture platformSpriteSheet;
    platformSpriteSheet.loadFromFile("assets/images/spritesheet.png");
    sf::Sprite earthsprite1(platformSpriteSheet);
    earthsprite1.setTextureRect(sf::IntRect(26, 95, 21, 21));

    sf::Texture PlayerTexture1;
    PlayerTexture1.loadFromFile("assets/images/slime.png.");
    sf::Sprite PlayerSprite1(PlayerTexture1);

    playerClass playerObj(PlayerSprite1);

    platformClass level[5] = {platformClass(100,200, earthsprite1),
                                platformClass(205,200, earthsprite1),
                                platformClass(310,200, earthsprite1),
                                platformClass(415,200, earthsprite1),
                                platformClass(520,200, earthsprite1),};

    sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(windowWidth,windowHeight));
    sf::Clock gameClock;

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        keyRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        keyLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        keyUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        keyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

        float deltatime = gameClock.getElapsedTime().asSeconds();

        playerObj.update(keyUp,keyDown,keyRight,keyLeft,level, deltatime);
        view.setCenter(sf::Vector2f(playerObj.image.getPosition().x+playerObj.image.getLocalBounds().width * playerObj.scale/0.2f,playerObj.image.getPosition().y+playerObj.image.getLocalBounds().height * playerObj.scale));
        gameClock.restart().asSeconds();

        window.setView(view);
        // Clear screen
        window.clear();

        window.draw(playerObj.image);

        for(int i = 0; i<5 ; i++){
            window.draw(level[i].image);
        }

    //    app.draw(helloText);

        //Sleep(1);





        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
