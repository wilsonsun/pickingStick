//
//  SetUp.cpp
//  PickingStick
//
//  Created by Wilson on 2016-10-31.
//  Copyright © 2016 Wilson. All rights reserved.
//

#include "SetUp.hpp"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

sf::Sprite loadBackGround() {
    sf::Texture backGroundTexture;
    
    if (!backGroundTexture.loadFromFile(resourcePath() + "background.jpg")) {
        std::cout << "Could NOT load background image" << std::endl;
    }
    sf::Sprite backGroundSprite(backGroundTexture);
    
    return backGroundSprite;
}
