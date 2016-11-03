
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "SetUp.hpp"
const float PLAYER_WIDTH = 32.0f;
const float PLAYER_HEIGHT = 32.0f;

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1500, 1200), "SFML window");
    //window.setKeyRepeatEnabled(false);
    // Set the Icon
    /*
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
     */
    
    float frameCounter = 0;
    float switchFrame = 100;
    float frameSpeed = 500;
    float adjustedSpeed = 10.0;
    bool isMoving = false;
    sf::Clock clock;
    
    sf::Texture playerTexture;
    enum state {Down, Left, Right, Up};
    sf::Vector2i source;
    source.x = 1;

    // Load a sprite to display
    if (!playerTexture.loadFromFile(resourcePath() + "charater.png")) {
        std::cout << "Could NOT load player image" << std::endl;
        return EXIT_FAILURE;
    }
    
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(100.0f, 100.0f);
    playerSprite.scale(3.0f, 3.0f);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    //music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                /*
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up) {
                        playerSprite.move(0, -1);
                        source.y = Up;
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        playerSprite.move(0, 1);
                        source.y = Down;
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        playerSprite.move(1, 0);
                        source.y = Right;
                    }
                    else if (event.key.code == sf::Keyboard::Left) {
                        playerSprite.move(-1, 0);
                        source.y = Left;
                    }
                    break;
                */
                default:
                    break;
                 
            }
            
            isMoving = false;
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                source.y = Up;
                playerSprite.move(0, -1*adjustedSpeed);
                isMoving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                playerSprite.move(0, 1*adjustedSpeed);
                source.y = Down;
                isMoving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerSprite.move(1*adjustedSpeed, 0);
                source.y = Right;
                isMoving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerSprite.move(-1*adjustedSpeed, 0);
                source.y = Left;
                isMoving = true;
            }
             
        }


        frameCounter += frameSpeed*clock.restart().asSeconds();
        //std:: cout << "---------------------" << std::endl;
        //std::cout << "frameCounter: " << frameCounter << std::endl;
        //std::cout << "switchFrame: " << switchFrame << std::endl;
        if (frameCounter >= switchFrame) {
            frameCounter = 0;
        // Animation
            if (isMoving) {
                if (source.x >= 2)
                    source.x = -1;
                source.x++;
            } else {
                source.x = 1;
            }
        
        }
        
        playerSprite.setTextureRect(sf::IntRect(source.x*PLAYER_WIDTH, source.y*PLAYER_HEIGHT,PLAYER_WIDTH,PLAYER_HEIGHT));

        
        // Draw the sprite
        window.draw(playerSprite);

        // Draw the string
        //window.draw(text);

        // Update the window
        window.display();
        // Clear screen
        window.clear();
    }

    return EXIT_SUCCESS;
}
