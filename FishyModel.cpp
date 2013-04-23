#include "FishyModel.hpp"

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Util.hpp"

FishyModel::FishyModel()
{
    m_gameSpeed = 1.0;

    m_curTime = 0;
    m_timeDue = 0;
    m_nextFishTime = 0;

    m_gameOver = false;

    m_player.pos.x = 0;
    m_player.pos.y = -4;
    m_player.vel.x = 0;
    m_player.vel.y = 5;
    m_player.acc.x = 0;
    m_player.acc.y = 0;
    m_player.size = 0.2;
    m_player.dir = 1;

    for(int i = 0; i < MAX_FISH; ++i) {
        m_fish[i] = NULL;
    }

    srand(time(0));
}

FishyModel::~FishyModel()
{
    for(int i = 0; i < MAX_FISH; ++i) {
        if(m_fish[i]) {
            delete m_fish[i];
        }
    }
}

void FishyModel::Simulate(const double dt)
{
    m_timeDue += dt;

    const double tickSize = 1/100.0;

    while(!IsGameOver() && m_timeDue >= tickSize) {
        Tick(tickSize * m_gameSpeed);
        m_timeDue -= tickSize;
        m_curTime += tickSize * m_gameSpeed;
    }
}

void FishyModel::Tick(const double dt)
{
    //Update player velocity
    m_player.vel.x += m_player.acc.x * dt;
    m_player.vel.y += m_player.acc.y * dt;

    //Apply drag to player's velocity
    m_player.vel.x -= m_player.vel.x * dt;
    m_player.vel.y -= m_player.vel.y * dt;

    //Update player's direction
    if(m_player.acc.x > 0) {
        m_player.dir = 1;
    } else if(m_player.acc.x < 0) {
        m_player.dir = -1;
    }

    //Move player
    m_player.pos.x += m_player.vel.x * dt;
    m_player.pos.y += m_player.vel.y * dt;

    //Tick all the fish
    for(int i = 0; i < MAX_FISH; ++i) {
        if(m_fish[i]) {
            m_fish[i]->Tick(dt);
        }
    }

    //Check for collision between player and fish
    {
        AABB pc, fc;
        GetPlayerAABB(pc);

        for(int i = 0; i < GetNumFish(); ++i) {
            if(m_fish[i]) {
                m_fish[i]->GetAABB(fc);

                //If Collision
                if(AABBIntersect(pc, fc)) {
                    if(m_player.size >= m_fish[i]->GetSize()) {
                        //  fish smaller -> player grows, fish dies
                        m_player.size += 0.005;
                        delete m_fish[i];
                        m_fish[i] = 0;
                        continue;
                    } else {
                        //  fish bigger  -> player dies, game over
                        m_gameOver = true;
                    }
                }
            }
        }
    }

    //Kill old fish
    {
        for(int i = 0; i < GetNumFish(); ++i) {
            const Fish* f = GetFish(i);

            if(f) {
                Vec2d vel, pos;
                f->GetPosition(pos);
                f->GetVelocity(vel);

                if((vel.x > 0 && pos.x > 8) || 
                   (vel.x < 0 && pos.x < -8)) {
                    delete f;
                    m_fish[i] = 0;
                }
            }
        }
    }

    //Add new fish
    if(GetTime() >= m_nextFishTime) {
        m_nextFishTime = GetTime() + 0.5;
        AddFish();
    }
}

void FishyModel::AddFish()
{
    int index = -1;

    for(int i = 0; i < GetNumFish(); ++i) {
        if(m_fish[i] == NULL) {
            index = i;
            break;
        }
    }

    //No available fish slots
    if(index < 0) {
        return;
    }

    Fish* fish = new Fish();
    m_fish[index] = fish;

    //Vertical position, from -4 to +4
    double yPos = ((rand() % 800) * 0.01) - 4;
    double size = m_player.size * (0.5 + 0.1 * (1 + rand() % 10));
    double speed = 1 + (rand() % 30) * 0.1;
    fish->SetSize(size);

    //Left or right side?
    if(rand() % 2) {
        //Left
        fish->SetPosition(-(9 + 2 * size), yPos);
        fish->SetVelocity(speed, 0);
    } else {
        //Right
        fish->SetPosition(9 + 2 * size, yPos);
        fish->SetVelocity(-speed, 0);
    }


}

void FishyModel::SetPlayerAccel(const Vec2d &a)
{
    const double speed = 8;

    if(a.x > 0) {
        m_player.acc.x = speed;
    } else if(a.x < 0) {
        m_player.acc.x = -speed;
    } else {
        m_player.acc.x = 0;
    }

    if(a.y > 0) {
        m_player.acc.y = speed;
    } else if(a.y < 0) {
        m_player.acc.y = -speed;
    } else {
        m_player.acc.y = 0;
    }
}

int FishyModel::GetPlayerDirection() const
{
    return m_player.dir;
}

void FishyModel::GetPlayerAABB(AABB &aabb) const
{
    aabb.p1.x = m_player.pos.x;
    aabb.p1.y = m_player.pos.y;
    aabb.p2.x = m_player.pos.x + m_player.size * 2;
    aabb.p2.y = m_player.pos.y + m_player.size * 1;
}

const double FishyModel::GetTime() const
{
    return m_curTime;
}

const bool FishyModel::IsGameOver() const
{
    return m_gameOver;
}

const int FishyModel::GetNumFish() const
{
    return MAX_FISH;
}

const Fish* FishyModel::GetFish(int i) const
{
    if(i < 0 || i >= GetNumFish())
        return NULL;

    return m_fish[i];
}

Fish::Fish()
{
    m_pos.x = 0;
    m_pos.y = 0;
    m_vel.x = 0;
    m_vel.y = 0;
    m_size = 0.2;
    m_dir = 1;
    m_time = 0;
}

Fish::~Fish()
{

}

void Fish::GetPosition(Vec2d &pos) const
{
    pos.x = m_pos.x;
    pos.y = m_pos.y + sin(m_time) / (m_vel.x + 0.1);
}

void Fish::SetPosition(const double x, const double y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void Fish::SetPosition(const Vec2d &pos)
{
    m_pos.x = pos.x;
    m_pos.y = pos.y;
}

void Fish::GetVelocity(Vec2d &vel) const
{
    vel.x = m_vel.x;
    vel.y = m_vel.y;
}

void Fish::SetVelocity(const double x, const double y)
{
    m_vel.x = x;
    m_vel.y = y;
}

void Fish::SetVelocity(const Vec2d &vel)
{
    m_vel.x = vel.x;
    m_vel.y = vel.y;
}

const int Fish::GetDirection() const
{
    return m_dir;
}

const double Fish::GetSize() const
{
    return m_size;
}

void Fish::SetSize(const double size)
{
    m_size = size;
}

void Fish::GetAABB(AABB &aabb) const
{
    GetPosition(aabb.p1);
    aabb.p2.x = aabb.p1.x + m_size * 2;
    aabb.p2.y = aabb.p1.y + m_size;
}

void Fish::Tick(const double dt)
{
    m_time += dt;

    m_pos.x += m_vel.x * dt;
    m_pos.y += m_vel.y * dt;

    if(m_vel.x > 0) {
        m_dir = 1;
    } else if(m_vel.x < 0) {
        m_dir = -1;
    }
}
