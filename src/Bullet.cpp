#include "Bullet.h"
Bullet::Bullet(int x, int y)
    : Entity(x, y, '|')
{
}
void Bullet::update()
{
    main_y--;
    if (main_y < 0)
    {
        main_alive = false;
    }
}
void Bullet::draw(std::vector<std::string> &buffer) const
{
    Entity::draw(buffer);
}