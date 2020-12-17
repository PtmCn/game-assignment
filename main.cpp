#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "./include/Entity.hpp"
#include "./include/Player.hpp"
#include "./include/Platform.hpp"

const int windowWidth = 1260;
const int windowHeight = 720;

using namespace std;

int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "mystery forest");

    bool W,A,S,D;

    int levelArray[10][10] = {{0,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,1,0,0,0,0},
                              {1,0,0,0,0,0,0,0,0,0},
                              {0,1,0,0,0,0,0,0,0,0},
                              {0,0,1,1,1,1,1,0,0,0},
                            };

    Platform** level = new Platform*[100];

    int sizeOfLevel = 0;

    for(int i = 0; i < 10 ; i++){
        for(int j = 0; j < 10; j++){
            if (levelArray[i][j] == 1){
                level[sizeOfLevel]->init( j * 15,i * 15, 15, 15);
                level[sizeOfLevel]->setTexture("assets/images/spritesheet.png");
                sizeOfLevel++;
            }
        }
    }

    Player player(200,200,60,60);
    player.setTexture("assets/images/slime.png");

    sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(windowWidth,windowHeight));
    view.zoom(0.1f);
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

        W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        float deltatime = gameClock.getElapsedTime().asSeconds();

        player(W,A,S,D,deltatime);
        view.setCenter(player.x + player.w/2.f,player.y + player.h/2.f);
        gameClock.restart().asSeconds();

        window.setView(view);
        // Clear screen
        window.clear();

        window.draw(player);

        for(int i = 0; i< sizeOfLevel ; i++){
            window.draw(level[i]);
        }

    //    app.draw(helloText);

        //Sleep(1);


        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
