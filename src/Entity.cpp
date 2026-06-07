#include "Entity.h"

Entity::Entity(int x, int y, char symbol)
    : main_x(x), main_y(y), main_symbol(symbol), main_alive(true)
{
}
void Entity::draw(std::vector<std::string> &buffer) const
{
    if (main_alive && main_x >= 0 && main_x < WIDTH && main_y >= 0 && main_y < HEIGHT)
    {
        buffer[main_y][main_x] = main_symbol;
    }
}
bool Entity::collidesWith(const Entity &other) const
{
    // 坐标和生存情况都相同，那就是撞上了
    return main_x == other.main_x && main_y == other.main_y && main_alive && other.main_alive;
}
bool Entity::isOutOfBounds() const
{
    return main_x < 0 || main_x >= WIDTH || main_y < 0 || main_y >= HEIGHT;
}
int Entity::getX() const
{
    return main_x;
}
int Entity::getY() const
{
    return main_y;
}
bool Entity::isAlive() const
{
    return main_alive;
}
void Entity::setAlive(bool alive)
{
    main_alive = alive;
}
