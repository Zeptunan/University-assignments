#include "Menu.h"

MenuItem::MenuItem(const std::string& buttonText, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
    : text(buttonText, font, characterSize), idleColor(sf::Color::White), hoverColor(sf::Color::Red) {
    // Set up menu text
    text.setFillColor(idleColor);
    text.setPosition(position);

    // Set up menu shape
    sf::FloatRect textBounds = text.getLocalBounds();
    shape.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
    shape.setFillColor(idleColor);
    shape.setPosition(position);
}

void MenuItem::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

bool MenuItem::isMouseOver(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition)) {
      text.setFillColor(sf::Color::Green);
        shape.setFillColor(hoverColor);
        return true;
    }
    else {
      text.setFillColor(sf::Color::Black);
        shape.setFillColor(idleColor);
        return false;
    }
}

bool MenuItem::isClicked(const sf::Vector2f& mousePosition) const {
    return shape.getGlobalBounds().contains(mousePosition);
}
//kodinnlämning