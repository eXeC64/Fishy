#include "Util.hpp"
#include <SFML/Graphics.hpp>

const bool AABBIntersect(const AABB &a, const AABB &b)
{
    //Check B tl within A
    if(b.p1.x >= a.p1.x && b.p1.x <= a.p2.x &&
       b.p1.y >= a.p1.y && b.p1.y <= a.p2.y) {
        return true;
    }

    //Check B br within A
    if(b.p2.x >= a.p1.x && b.p2.x <= a.p2.x &&
       b.p2.y >= a.p1.y && b.p2.y <= a.p2.y) {
        return true;
    }
    
    //Check B tr within A
    if(b.p2.x >= a.p1.x && b.p2.x <= a.p2.x &&
       b.p1.y >= a.p1.y && b.p1.y <= a.p2.y) {
        return true;
    }

    //Check B bl within A
    if(b.p1.x >= a.p1.x && b.p1.x <= a.p2.x &&
       b.p2.y >= a.p1.y && b.p2.y <= a.p2.y) {
        return true;
    }

    //Check A tl within B
    if(a.p1.x >= b.p1.x && a.p1.x <= b.p2.x &&
       a.p1.y >= b.p1.y && a.p1.y <= b.p2.y) {
        return true;
    }

    //Check A br within B
    if(a.p2.x >= b.p1.x && a.p2.x <= b.p2.x &&
       a.p2.y >= b.p1.y && a.p2.y <= b.p2.y) {
        return true;
    }

    //Check A tr within B
    if(a.p2.x >= b.p1.x && a.p2.x <= b.p2.x &&
       a.p1.y >= b.p1.y && a.p1.y <= b.p2.y) {
        return true;
    }

    //Check A bl within B
    if(a.p1.x >= b.p1.x && a.p1.x <= b.p2.x &&
       a.p2.y >= b.p1.y && a.p2.y <= b.p2.y) {
        return true;
    }

    return false;
}

const double LInterp(const double val, const double min, const double max)
{
    if(val <= 0) {
        return min;
    } else if(val >= 1) {
        return max;
    } else {
        return min + (max - min) * val;
    }
}

void ConstructFish(sf::ConvexShape &body, sf::ConvexShape &tail, const AABB &shape, int direction)
{
    body.setPointCount(6);
    tail.setPointCount(3);
    if(direction < 0) {
        body.setPoint(0, sf::Vector2f(shape.p1.x, LInterp(0.5, shape.p1.y, shape.p2.y)));
        body.setPoint(1, sf::Vector2f(LInterp(0.05, shape.p1.x, shape.p2.x), shape.p1.y));
        body.setPoint(2, sf::Vector2f(LInterp(0.50, shape.p1.x, shape.p2.x), shape.p1.y));
        body.setPoint(3, sf::Vector2f(LInterp(0.95, shape.p1.x, shape.p2.x), LInterp(0.5, shape.p1.y, shape.p2.y)));
        body.setPoint(4, sf::Vector2f(LInterp(0.50, shape.p1.x, shape.p2.x), shape.p2.y));
        body.setPoint(5, sf::Vector2f(LInterp(0.05, shape.p1.x, shape.p2.x), shape.p2.y));
        tail.setPoint(0, sf::Vector2f(LInterp(0.75, shape.p1.x, shape.p2.x), LInterp(0.5, shape.p1.y, shape.p2.y)));
        tail.setPoint(1, sf::Vector2f(shape.p2.x, shape.p1.y));
        tail.setPoint(2, sf::Vector2f(shape.p2.x, shape.p2.y));
    } else {
        body.setPoint(0, sf::Vector2f(shape.p2.x, LInterp(0.5, shape.p1.y, shape.p2.y)));
        body.setPoint(1, sf::Vector2f(LInterp(0.95, shape.p1.x, shape.p2.x), shape.p1.y));
        body.setPoint(2, sf::Vector2f(LInterp(0.50, shape.p1.x, shape.p2.x), shape.p1.y));
        body.setPoint(3, sf::Vector2f(LInterp(0.05, shape.p1.x, shape.p2.x), LInterp(0.5, shape.p1.y, shape.p2.y)));
        body.setPoint(4, sf::Vector2f(LInterp(0.50, shape.p1.x, shape.p2.x), shape.p2.y));
        body.setPoint(5, sf::Vector2f(LInterp(0.95, shape.p1.x, shape.p2.x), shape.p2.y));
        tail.setPoint(0, sf::Vector2f(LInterp(0.25, shape.p1.x, shape.p2.x), LInterp(0.5, shape.p1.y, shape.p2.y)));
        tail.setPoint(1, sf::Vector2f(shape.p1.x, shape.p1.y));
        tail.setPoint(2, sf::Vector2f(shape.p1.x, shape.p2.y));
    }
}
