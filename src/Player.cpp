#include "Player.h"
Player::Player(int x, int y)
    : Entity(x, y, 'A'), main_fireCooldown(0)
{
}
void Player::move(Direction dir)
{
    switch (dir)
    {
    case Direction::UP:
        if (main_y > 0)
        {
            main_y--;
        }
        break;
    case Direction::DOWN:
        if (main_y < HEIGHT - 1)
        {
            main_y++;
        }
        break;
    case Direction::LEFT:
        if (main_x > 0)
        {
            main_x--;
        }
        break;
    case Direction::RIGHT:
        if (main_x < WIDTH - 1)
        {
            main_x++;
        }
        break;
    default:
        break;
    }
}
bool Player::tryfire()
{
    if (
        main_fireCooldown == 0)
    {
        main_fireCooldown = FIRECOOL;
        return true;
    }
    return false;
}
void Player::update()
{
    if (main_fireCooldown > 0)
    {
        main_fireCooldown--;
    }
}
void Player::draw(std::vector<std::string> &buffer) const
{
    Entity::draw(buffer);
}