#include <iostream>
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Level.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window3d(sf::VideoMode(1280, 720), "RayCaster - 3D", sf::Style::Close);
    sf::RenderWindow window2d(sf::VideoMode(512, 512), "RayCaster - 2D", sf::Style::Close);
    sf::Clock deltaClock;

    Controller playerController;
    Level level = Level("./Levels/LevelTest.txt");
    Player player = Player(playerController, level);

    while (window2d.isOpen())
    {
        // Check if window 3d was closed
        sf::Event event3d;
        if (window3d.pollEvent(event3d))
        {
            // If window is closed
            if (event3d.type == sf::Event::Closed)
            {
                window2d.close();
                window3d.close();
            }
        }

        // Check if window 2d was closed
        sf::Event event2d;
        while (window2d.pollEvent(event2d))
        {
            // If window is closed
            if (event2d.type == sf::Event::Closed)
            {
                window2d.close();
                window3d.close();
            }
            // If a key is pressed
            if (event2d.type == sf::Event::KeyPressed)
                playerController.keyEvent(event2d.key.code, true);
            // If a key is released
            if (event2d.type == sf::Event::KeyReleased)
                playerController.keyEvent(event2d.key.code, false);
        }
        
        float deltaTime = deltaClock.restart().asSeconds();
        player.updatePlayerLocation(deltaTime);
        
        // Update window 2d
        window2d.clear();
        window2d.draw(player.getCircleShape());
        window2d.draw(player.getRectangleShape());
        window2d.display();
    }

    return 0;
}