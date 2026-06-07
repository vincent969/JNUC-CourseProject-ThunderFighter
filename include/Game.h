#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
class Game
{
private:
    Player main_player;
    std::vector<std::unique_ptr<Entity>> main_enemies;
    std::vector<std::unique_ptr<Entity>> main_bullets;
    int main_score;
    bool if_running;
    int frame_counter;

public:
    Game();
    void run();

private:
    // 界面
    void showStartScreen();
    bool showGameOverScreen();
    // 游戏循环
    void handleInput();    // 键盘输入
    void fireBullet();     // 射击辅助
    void updateEntities(); // 更新实体
    void checkCollisions();
    void spawnEnemies();
    void renderEntities(); // 渲染实体
    void removeEntities(); // 删除实体
    // 控制台的显示辅助
    static void clearScreen();
    static void setCursorPosition(int x, int y);
    static void hideCursor(); // 光标
    static void showCursor();
};
#endif
