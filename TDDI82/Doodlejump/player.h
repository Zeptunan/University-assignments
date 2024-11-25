#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "entity.h"

class Player : public Entity
{
public:
    Player (float x, float y);
    Player(sf::Vector2f ePos = sf::Vector2f());
    void draw(sf::RenderTarget &) override;
    void handle_input();
    void update() override;
    void setSprite(std::string) override;
    void getShield();
    void loseShield();

    sf::Vector2f getOrigin();

    float van_halen();
    void collision(Entity &ent) override;
    
    sf::Rect<float> getPlatDetection() override;
    sf::Rect<float> getGlobalBounds() override;
    bool hitPlat{false};
    //bool hasShield{true} override;
    float accel;

private:
    sf::RectangleShape chara;
    sf::Texture snubbe_left;
    sf::Texture snubbe_right;
    sf::Texture snubbe_left_jump;
    sf::Texture snubbe_right_jump;
    sf::Texture snubbe_left_shield;
    sf::Texture snubbe_right_shield;
    sf::Vector2f top_left{30.0, 100.0-15.0};
    sf::Vector2f top_right{100.0-30.0, 100.0-15.0};
    sf::Vector2f bott_left{100.0-90.0, 90.0};  
    sf::Vector2f bott_right{90.0, 90.0};
    

    bool facing_left{true};
};

#endif
