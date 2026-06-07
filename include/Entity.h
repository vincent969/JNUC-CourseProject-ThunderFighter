#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "Constant.h"
#include <string>
class Entity
{
protected:
    int main_x, main_y;
    char main_symbol;
    bool main_alive;

public:
    // 构造和析构函数
    Entity(int x, int y, char symbol);
    virtual ~Entity() = default; // 自动生成默认的析构函数,更加现代
    virtual void update() = 0;
    virtual void draw(std::vector<std::string> &buffer) const = 0;
    // std::vector<std::string>& buffer 这是传进来的屏幕缓冲区
    bool collidesWith(const Entity &other) const;
    bool isOutOfBounds() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    void setAlive(bool alive);
};
#endif