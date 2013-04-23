#pragma once
namespace sf {
    class ConvexShape;
}

struct Vec2d {
    double x;
    double y;
};

struct AABB {
    Vec2d p1;
    Vec2d p2;
};

const bool AABBIntersect(const AABB &a, const AABB &b);
const double LInterp(const double val, const double min, const double max);
void ConstructFish(sf::ConvexShape &body, sf::ConvexShape &tail, const AABB &shape, int direction);
