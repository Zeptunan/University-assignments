#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class MenuItem {
private:
    sf::Text text;
    sf::RectangleShape shape;
    sf::Color idleColor;
    sf::Color hoverColor;

public:
    MenuItem(const std::string& buttonText, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) const;
    bool isMouseOver(const sf::Vector2f& mousePosition);
    bool isClicked(const sf::Vector2f& mousePosition) const;
};

#endif // MENU_H
//kodinnlämning