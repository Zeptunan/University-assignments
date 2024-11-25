#ifndef PLATFORM_H
#define PLATFORM_H

#include "entity.h"
#include <SFML/Graphics.hpp>

class Platform : public Entity {
public:
    Platform( float, float);
    Platform( sf::Vector2f pos = sf::Vector2f());

    void draw(sf::RenderTarget & ) override;
    void update() override;
    
    void collision(Entity &) override;

    sf::Rect<float> getGlobalBounds() override;
    sf::Rect<float> getPlatDetection() override;
    void setSprite(std::string) override;

protected:
    sf::Texture *pTexture;
};


class Red_Platform : public Platform {
public:
    Red_Platform( float, float);
    Red_Platform( sf::Vector2f pos = sf::Vector2f());

    //void update() override;
    void collision(Entity &) override;

    //void setSprite(std::string) override;

private:
};


class Blue_Platform : public Platform {
public:
    Blue_Platform( float, float);
    Blue_Platform( sf::Vector2f pos = sf::Vector2f());

    void update() override;
    // void collision(Entity &) override;

private:
    float direction = 1;
};

#endif //PLATFORM_H
//kodinnlämning