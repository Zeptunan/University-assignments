#include "entity.h"


Entity::Entity()
 : ID{"default"}, sprite{}
{

}

Entity::Entity(std::string ID, sf::Vector2f pos)
 : ID{ID}, sprite{}
{
    sprite.setPosition(pos);
}

std::string Entity::getID() const 
{
    return this->ID;
}


sf::Vector2f Entity::getPos() const
{
    return sprite.getPosition();
}

void Entity::setPos(sf::Vector2f ePos)
{
    sprite.setPosition(ePos);
}

void Entity::move(sf::Vector2f const & val) 
{
    sprite.move(val);
}

void Entity::move(float const & x, float const & y)
{
    sf::Vector2f val(x, y);
    sprite.move(val);
}

float Entity::getAccel() {
    return accel;
};

void Entity::setAccel(float nAccel) {
    accel = nAccel;
};
