#include <iostream>
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Level.h"
#include "Player.h"
#include "Renderer2D.h"
#include "LineTracer.h"
#include "Renderer3D.h"

int main()
{
    sf::RenderWindow window3d(sf::VideoMode(1280, 720), "RayCaster - 3D", sf::Style::Close);
    sf::RenderWindow window2d(sf::VideoMode(512, 512), "RayCaster - 2D", sf::Style::Close);
    sf::Clock deltaClock;

    Controller playerController;
    Level level = Level("./Levels/LevelTest.txt");
    Player player = Player(playerController, level);

    Renderer2D renderer2d = Renderer2D(window2d, level, player);
    LineTracer lineTracer = LineTracer(level);

    Renderer3D renderer3d = Renderer3D(1280, window3d, 110, 320, level, player);

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
        
        std::cout << 1 / deltaTime << std::endl;
        
        // Update window 2d
        renderer2d.render();
       
        sf::CircleShape interCircle(0.1f);
        interCircle.setFillColor(sf::Color::Red);
        interCircle.setOrigin(interCircle.getRadius(), interCircle.getRadius());

        for (int i = -50; i < 50; i++)
        {
            Intersection intersection = lineTracer.findIntersection(player.getPositionX(), player.getPositionY(), player.getAngle() - i);
            interCircle.setPosition(intersection.getX(), intersection.getY());
            window2d.draw(interCircle);
        }

        window2d.display();
    }

    return 0;
}