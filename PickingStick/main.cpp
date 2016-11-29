
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

void isCollided (sf::Sprite &player, sf::Sprite &ball, int &points, sf::Text &text, sf::Font &font) {
    
    sf::FloatRect playerRect = player.getGlobalBounds();
    sf::FloatRect ballRect = ball.getGlobalBounds();
    
    if (playerRect.intersects(ballRect)) {
        ++points;
        std::string stringPoints = "Points:";
        std::string displayText = stringPoints+=std::to_string(points);
        text.setString(displayText);
        float rx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1400));
        float ry = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1100));
        
        ball.setPosition(rx, ry);
    }
    
    return;
    
}


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1500, 1200), "SFML window");
    window.setFramerateLimit(60);
    //window.setKeyRepeatEnabled(false);
    // Set the Icon
    /*
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
     */
    
    int points = 0;
    std::string stringPoints = "Points:";
    float frameCounter = 0;
    float switchFrame = 100;
    float frameSpeed = 500;
    float adjustedSpeed = 15.0;
    bool isMoving = false;
    sf::Clock clock;
    
    sf::Texture playerTexture;
    sf::Sprite backGround;
    enum state {Down, Left, Right, Up};
    sf::Vector2i source;
    source.x = 1;
    
    
    // Loading background image
    sf::Texture backGroundTexture;
    
    if (!backGroundTexture.loadFromFile(resourcePath() + "background.jpg")) {
        std::cout << "Could NOT load background image" << std::endl;
    }
    sf::Sprite backGroundSprite(backGroundTexture);
    backGroundSprite.scale(2.0f, 2.0f);
    
    // Load a ball
    sf::Texture ballTexture;
    if (!ballTexture.loadFromFile(resourcePath() + "ball.png")) {
        std::cout << "Could NOT load ball image" << std::endl;
    }
    sf::Sprite ballSprite(ballTexture);
    ballSprite.setScale(0.1f, 0.1f);
    float rx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1400));
    float ry = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1100));
    ballSprite.setPosition(rx, ry);
    
    
    // Load a sprite to display
    if (!playerTexture.loadFromFile(resourcePath() + "charater.png")) {
        std::cout << "Could NOT load player image" << std::endl;
        return EXIT_FAILURE;
    }
    
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(100.0f, 100.0f);
    playerSprite.scale(4.0f, 4.0f);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    std::string displayText = stringPoints+=(points+'0');
    sf::Text text(displayText, font, 50);
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

        isCollided(playerSprite, ballSprite, points, text, font);

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

        
        window.draw(backGroundSprite);
        // Draw the ball
        window.draw(ballSprite);
        // Draw the sprite
        window.draw(playerSprite);

        window.draw(text);
        
        
        
        // Update the window
        window.display();
        // Clear screen
        window.clear();
    }

    return EXIT_SUCCESS;
}
