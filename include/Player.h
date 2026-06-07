#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Direction.h"
class Player : public Entity
{
private:
    int main_fireCooldown;
    /// 冷却剩余时间，>0的时候不能开火
public:
    Player(int x, int y);
    void move(Direction dir);
    bool tryfire();
    void update() override;
    void draw(std::vector<std::string> &buffer) const override;
};
#endif