#pragma once

#include <SFML/Graphics.hpp>

class FishyModel;

class FishyView
{
public:
    FishyView();
    ~FishyView();

    void            SetModel(FishyModel* model);
    void            Draw(sf::RenderTarget* rt)          const;
private:
    FishyModel*   m_model;
};
