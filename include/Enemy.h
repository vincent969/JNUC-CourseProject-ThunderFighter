#ifndef ENEMY_H

#define ENEMY_H
#include "Entity.h"
class Enemy : public Entity
{
public:
    Enemy(int x, int y);
    void update() override;
    void draw(std::vector<std::string> &buffer) const override;
};

#endif