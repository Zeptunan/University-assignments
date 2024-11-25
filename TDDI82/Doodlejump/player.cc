#include "player.h"
#include <iostream>

Player::Player (float x, float y)
    : Player(sf::Vector2f(x,y))
{} 

Player::Player(sf::Vector2f pos)
    : Entity {"player", pos}
{
    if (!snubbe_left.loadFromFile("resources/snubbe_left.png"))
    {
        std::cout << "Load failed" << std::endl;

        system("pause");
    }
    if (!snubbe_right.loadFromFile("resources/snubbe_right.png"))
    {
        std::cout << "Load failed" << std::endl;

        system("pause");
    }
    if (!snubbe_left_jump.loadFromFile("resources/snubbe_left_jump.png"))
    {
        std::cout << "Load failed" << std::endl;

        system("pause");
    }
    if (!snubbe_right_jump.loadFromFile("resources/snubbe_right_jump.png"))
    {
        std::cout << "Load failed" << std::endl;

        system("pause");
    }
    if (!snubbe_right_shield.loadFromFile("resources/snubbe_right_shield.png"))
    {
        std::cout << "Load failed" << std::endl;

        system("pause");
    }
    if (!snubbe_left_shield.loadFromFile("resources/snubbe_left_shield.png"))
    {
        std::cout << "Load failed" << std::endl;

        system("pause");
    }

    sprite.setTexture(snubbe_left);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
}

void Player::draw(sf::RenderTarget &window)
{
    window.draw(sprite);
}

void Player::update()
{
    handle_input();
    if (sprite.getPosition().y > 960) {
        isAlive = false;
    }
    else{
        isAlive = true;
    }
}

void Player::handle_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        facing_left = true;
        if (hasShield) 
        {
            sprite.setTexture(snubbe_left_shield);
        }
        else
        { 
            sprite.setTexture(snubbe_left);
        }
        move(-5.0, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        facing_left = false;
        if (hasShield) 
        {
            sprite.setTexture(snubbe_right_shield);
        }
        else
        { 
            sprite.setTexture(snubbe_right);
        }
        move(5.0, 0);
    }

    if ( sprite.getPosition().x + sprite.getGlobalBounds().width/2 > 640+100 )
    {
        sprite.setPosition(-(sprite.getGlobalBounds().width/2) , sprite.getPosition().y);
    }
    else if ( sprite.getPosition().x < (0 - sprite.getGlobalBounds().width/2) )
    {
        sprite.setPosition( ((640+100) - sprite.getGlobalBounds().width/2) , sprite.getPosition().y);
    }
}

sf::Vector2f Player::getOrigin()
{
    return sprite.getOrigin();
}

float Player::van_halen()
{
    if (facing_left)                //animation needs to be slower
    {
        sprite.setTexture(snubbe_left_jump);
    }
    else
    {
        sprite.setTexture(snubbe_right_jump);
    }

   

    if (facing_left)
    {
        sprite.setTexture(snubbe_left);
    }
    else
    {
        sprite.setTexture(snubbe_right);
    }
    return -11;
}

sf::Rect<float> Player::getPlatDetection()
{
    sf::Rect<float> bounds_left{std::min(top_left.x, bott_right.x), std::min(top_left.y, bott_right.y), std::abs(top_left.x - bott_right.x), std::abs(top_left.y - bott_right.y)};
    sf::Rect<float> bounds_right{(std::min(top_right.x, bott_left.x)), (std::min(top_right.y, bott_left.y)), std::abs(top_right.x - bott_left.x), std::abs(top_right.y - bott_left.y)};
    if (facing_left)
    {
        return sprite.getTransform().transformRect(bounds_left);
    }

    return sprite.getTransform().transformRect(bounds_right);
}

sf::Rect<float> Player::getGlobalBounds()
{
        return sprite.getGlobalBounds();    
}

void Player::setSprite(std::string newSprite) {}

void Player::getShield() 
{
    while (hasShield)
    {
        if (facing_left)
        {
            sprite.setTexture(snubbe_left_shield);
        }
        else
        {
            sprite.setTexture(snubbe_right_shield);
        }
    }
}

void Player::loseShield()
{
    while (!hasShield)
    {
        if (facing_left)
        {
            sprite.setTexture(snubbe_left);
        }
        else
        {
            sprite.setTexture(snubbe_right);
        }
    }
}

void Player::collision(Entity &ent) {
  if (ent.getID() == "Power_up") {
    hitPlat = true;
  } else {
    hitPlat = false;     
  }
}
  
