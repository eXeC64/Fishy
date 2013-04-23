#include "Game.hpp"

#include "FishyModel.hpp"
#include "FishyView.hpp"

Game::Game()
{
    m_model = 0;
    m_window = 0;
}

Game::~Game()
{
    if(m_model)
        delete m_model;

    if(m_window)
        delete m_window;
}

void Game::Run()
{
    if(m_model) {
        delete m_model;
    }

    m_model = new FishyModel();

    FishyView view;
    view.SetModel(m_model);

    m_window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Fishy");
    m_window->setFramerateLimit(60);

    bool paused = false;

    sf::Clock clock;
    while(m_window->isOpen())
    {
        sf::Event e;
        while(m_window->pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                m_window->close();

            if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Space) {
                    paused = !paused;
                }

                if(e.key.code == sf::Keyboard::R) {
                    delete m_model;
                    m_model = new FishyModel();
                    view.SetModel(m_model);
                }

                if(e.key.code == sf::Keyboard::F) {
                    m_model->AddFish();
                }

            }

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window->close();
        }
        
        {
            Vec2d a = {.x = 0, .y = 0};

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                a.x += 1;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                a.x -= 1;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                a.y += 1;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                a.y -= 1;
            }

            m_model->SetPlayerAccel(a);
        }


        double dt = clock.restart().asSeconds();

        //Prevent time from building up when stopped by a debugger
        if(dt >= 1) {
            dt = 0.01;
        }

        if(!paused) {
            m_model->Simulate(dt);
        }

        m_window->clear();
        view.Draw(m_window);
        m_window->display();
    }
}

