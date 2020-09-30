#include <SFML/Graphics.hpp>
#include <iostream>

int windowWidth = 400;
int windowHeight = 300;

using namespace sf;
using namespace std;

class playerClass{
    public:
        bool playerFaceRight = true;
        float xpos;
        float ypos;
        float xvel;
        float yvel;
        playerClass(){
            playerFaceRight = true;
            xpos = 0;
            ypos = 0;
            xvel = 0;
            yvel = 0;


        }
        void update(bool playerUp,bool playerDown,bool playerRight,bool playerLeft){
           if (playerRight){
                playerFaceRight = true;
                xvel = 1;
           }
           if (playerLeft){
                playerFaceRight = false;
                xvel = -1;
           }
           if (playerUp){
                yvel = -1;
           }
           if (playerDown){
                yvel = 1;
           }
           else if (!playerRight && !playerLeft && !playerUp && !playerDown)
           {
                 xvel = 0 ;
                 yvel = 0 ;
           }
           xpos += xvel;
           ypos += yvel;
        }
};

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(windowWidth, windowHeight), "Game");

    bool playerUp, playerDown, playerLeft, playerRight = false;

    playerClass playerObject;

    Texture slimeTexture;
    slimeTexture.loadFromFile("data/images/slime.png");
    Sprite slimeSprite(slimeTexture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
        playerRight = Keyboard::isKeyPressed(Keyboard::D);
        playerLeft = Keyboard::isKeyPressed(Keyboard::A);
        playerUp = Keyboard::isKeyPressed(Keyboard::W);
        playerDown = Keyboard::isKeyPressed(Keyboard::S);
        playerObject.update(playerUp,playerDown,playerRight,playerLeft);
        // Clear screen
        app.clear();

        app.draw(slimeSprite);

        slimeSprite.move(Vector2f(playerObject.xvel,playerObject.yvel));

        // Draw the sprite


        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
