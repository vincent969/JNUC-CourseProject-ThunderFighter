// 子弹
#ifndef BULLET_h
#define BULLET_h
#include "Entity.h"
class Bullet : public Entity
{
public:
    Bullet(int x, int k);
    void update() override;
    void draw(std::vector<std::string> &buffer) const override;
    // 重写父类的更新和绘制函数
};

#endif