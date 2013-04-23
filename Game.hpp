#pragma once

#include <SFML/Graphics.hpp>

class FishyModel;
class Game
{
public:
    Game();
    ~Game();

    void                Run();

private:
    FishyModel*         m_model;
    sf::RenderWindow*   m_window;
};
