#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Entity {
public:
    Entity();
    Entity( std::string ID, sf::Vector2f pos);

    std::string getID() const;

    sf::Vector2f getPos() const;
    void setPos( sf::Vector2f pos );

    virtual void draw (sf::RenderTarget & ) = 0;
    virtual void update() = 0;

    void move(sf::Vector2f const & val);
    void move(float const & x, float const & y);

    virtual sf::Rect<float> getGlobalBounds() = 0;
    virtual sf::Rect<float> getPlatDetection() = 0; //only for player

    virtual void setSprite(std::string) = 0;
    virtual void collision(Entity &) = 0;

    float getAccel();
    void setAccel(float);

    bool isAlive{true};
    bool hasShield{false};
protected:
    std::string ID;
    sf::Sprite sprite;
    float accel{0};





};

#endif