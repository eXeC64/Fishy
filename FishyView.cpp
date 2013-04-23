#include "FishyView.hpp"

#include <math.h>
#include <stdio.h>

#include "FishyModel.hpp"
#include "Util.hpp"


FishyView::FishyView()
{
    m_model = 0;
}

FishyView::~FishyView()
{
}

void FishyView::SetModel(FishyModel* model)
{
    m_model = model;
}

void FishyView::Draw(sf::RenderTarget* rt) const
{
    if(!m_model) {
        return;
    }

    const double zoom = 1.0;
    const double w = zoom * 16;
    const double h = zoom * 9;
    sf::View view(sf::FloatRect(-w/2,-h/2,w,h));

    rt->setView(view);

    //Draw bg
    {
        sf::RectangleShape bgRect(sf::Vector2f(16,9));
        bgRect.setPosition(-8,-4.5);
        bgRect.setFillColor(sf::Color(0,32,96));
        rt->draw(bgRect);
    }

    //Draw player
    {
        AABB pb;
        m_model->GetPlayerAABB(pb);
        sf::ConvexShape pBody(6);
        sf::ConvexShape pTail(3);
        int dir = m_model->GetPlayerDirection();
        ConstructFish(pBody, pTail, pb, dir);
        pBody.setFillColor(sf::Color(255,255,255));
        pTail.setFillColor(sf::Color(255,255,255));
        rt->draw(pBody);
        rt->draw(pTail);
    }


    //Draw fish
    {
        for(int i = 0; i < m_model->GetNumFish(); i++) {
            const Fish* f = m_model->GetFish(i);

            if(f) {
                AABB fb;
                f->GetAABB(fb);
                sf::ConvexShape body(6);
                sf::ConvexShape tail(3);
                ConstructFish(body, tail, fb, f->GetDirection());

                body.setFillColor(sf::Color(255,0,0));
                tail.setFillColor(sf::Color(255,0,0));
                rt->draw(body);
                rt->draw(tail);
            }
        }
    }

}

