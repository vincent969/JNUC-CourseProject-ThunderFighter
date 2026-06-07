#include "Enemy.h"
Enemy::Enemy(int x, int y)
    : Entity(x, y, 'V')
{
}
void Enemy::update()
{
    main_y++;
    if (main_y >= HEIGHT)
    {
        main_alive = false;
    }
}
void Enemy::draw(std::vector<std::string> &buffer) const
{
    Entity::draw(buffer);
}