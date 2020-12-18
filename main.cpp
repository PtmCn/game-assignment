#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
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


    sf::Texture playerTex;
    sf::Texture platformsTex;
    sf::Texture platformsTex2;
    sf::Texture platformsTex3;

    playerTex.loadFromFile("assets/images/Player.png");
    platformsTex.loadFromFile("assets/images/grass.png");
    platformsTex2.loadFromFile("assets/images/wall r.png");
    platformsTex3.loadFromFile("assets/images/goal.png");

    int levelArray[15][15] = {{2,3,0,0,0,0,0,0,0,0,0,0,0,0,2},
                              {2,1,1,1,1,1,1,0,0,1,1,1,0,0,2},
                              {2,0,0,0,0,0,0,0,1,0,0,0,0,1,2},
                              {2,0,0,0,1,0,0,0,0,0,0,0,1,0,2},
                              {2,0,0,1,1,1,1,1,1,0,0,1,0,0,2},
                              {2,1,0,0,0,0,0,0,0,0,0,0,0,0,2},
                              {2,1,1,1,1,1,0,0,0,0,0,0,0,0,2},
                              {2,0,0,0,0,0,1,0,0,0,0,0,0,0,2},
                              {2,0,0,0,0,0,0,0,1,0,0,0,0,0,2},
                              {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                            };

    std::vector<Platform> level;

    for(int i = 0; i < 15 ; i++){
        for(int j = 0; j < 15; j++){
            if (levelArray[i][j] == 1){
                Platform p( j * 46,i * 46, 46, 46, platformsTex);
                level.push_back(p);
            }
            else if (levelArray[i][j] == 2){
                Platform p( j * 46,i * 46, 46, 46, platformsTex2);
                level.push_back(p);
            }
            else if (levelArray[i][j] == 3){
                Platform p( j * 46,i * 46, 46, 46, platformsTex3);
                level.push_back(p);
            }
        }
    }

    Player player(80,382,32,32, playerTex);

    sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(windowWidth,windowHeight));
    window.setFramerateLimit(60);

    view.zoom(0.4f);

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

        player.update(W,A,S,D,level);
        if(player.getPosition().x == 94 && player.getPosition().y < 46)break;//endgame
        view.setCenter(player.getPosition().x + player.size.x/2.f,player.getPosition().y + player.size.y/2);

        window.setView(view);
        // Clear screen
        window.clear();

        window.draw(player);

        for(Platform& p : level){
            window.draw(p);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
