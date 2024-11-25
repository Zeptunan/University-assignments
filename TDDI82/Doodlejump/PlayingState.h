#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "GameState.h"
#include "world.h"

class PlayingState : public GameState {
public:
    PlayingState();
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

    bool isGameOver() const;

private:
    World world;
    bool gameOver;
};

#endif // PLAYINGSTATE_H
