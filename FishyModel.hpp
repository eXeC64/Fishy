#pragma once

#define MAX_FISH 32

#include "Util.hpp"

class Fish;

class FishyModel
{
public:
    FishyModel();
    ~FishyModel();

    void            Simulate(const double dt);
    void            SetPlayerAccel(const Vec2d &a);
    int             GetPlayerDirection()                const;
    void            GetPlayerAABB(AABB &aabb)           const;
    const double    GetTime()                           const;
    const bool      IsGameOver()                        const;
    const int       GetNumFish()                        const;
    const Fish*     GetFish(const int i)                const;
    void            AddFish();

private:
    void            Tick(const double dt);


    double          m_gameSpeed;
    double          m_curTime;
    double          m_timeDue;
    double          m_nextFishTime;

    struct {
        Vec2d pos;
        Vec2d vel;
        Vec2d acc;
        double size;
        int dir;
    }               m_player;

    Fish*           m_fish[MAX_FISH];

    bool            m_gameOver;
};

class Fish
{
public:
    Fish();
    ~Fish();

    void            GetPosition(Vec2d &pos)             const;
    void            SetPosition(const double x,
                                const double y);
    void            SetPosition(const Vec2d &pos);
    void            GetVelocity(Vec2d &vel)             const;
    void            SetVelocity(const double x,
                                const double y);
    void            SetVelocity(const Vec2d &vel);
    const int       GetDirection()                      const;
    const double    GetSize()                           const;
    void            SetSize(const double size);
    void            GetAABB(AABB &aabb)                 const;
    void            Tick(const double dt);

private:
    Vec2d           m_pos;
    Vec2d           m_vel;
    double          m_size;
    int             m_dir;
    double          m_time;
};

