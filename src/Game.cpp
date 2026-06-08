#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
Game::Game() : main_player(WIDTH / 2, HEIGHT - 1), main_score(0),
               if_running(true), frame_counter(0)
{
}
void Game::run()
{
    showStartScreen();
    clearScreen();
    hideCursor();
    while (if_running)
    {
        handleInput();
        updateEntities();
        spawnEnemies();
        checkCollisions();
        removeEntities();
        renderEntities();
        Sleep(FRAME_DELAY);
    }
    bool replay = showGameOverScreen();
    showCursor();
    if (replay)
    {
        Game newGame;
        newGame.run(); // 相当于重新开始
    }
}
void Game::handleInput()
{
    while (_kbhit())
    {
        int ch = _getch();
        Direction dir = Direction::NONE;
        if (ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
            case 72:
                dir = Direction::UP;
                break;
            case 80:
                dir = Direction::DOWN;
                break;
            case 75:
                dir = Direction::LEFT;
                break;
            case 77:
                dir = Direction::RIGHT;
                break;
            }
        }
        else if (ch == 'w' || ch == 'W')
            dir = Direction::UP;
        else if (ch == 's' || ch == 'S')
            dir = Direction::DOWN;
        else if (ch == 'a' || ch == 'A')
            dir = Direction::LEFT;
        else if (ch == 'd' || ch == 'D')
            dir = Direction::RIGHT;
        else if (ch == 'j' || ch == 'J')
            fireBullet();
        else if (ch == 27)
        {
            if_running = false;
            return;
        }
        if (dir != Direction::NONE)
            main_player.move(dir);
    }
}

void Game::spawnEnemies()
{
    if (main_enemies.size() >= MAX_ENEMIES)
        return;
    if (rand() % 100 < CREATE_CHANCE)
    {
        int x = rand() % (WIDTH - CREAT_MARGIN * 2) + CREAT_MARGIN;
        // 检查同列顶部是否已有敌人
        for (const auto &enemy : main_enemies)
        {
            if (enemy->isAlive() && enemy->getX() == x)
                return;
        }
        main_enemies.push_back(std::unique_ptr<Entity>(new Enemy(x, 0)));
    }
}

void Game::showStartScreen()
{
    clearScreen();
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════╗\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ║         雷霆战机                 ║\n";
    std::cout << "  ║         THUNDER FIGHTER          ║\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ╠══════════════════════════════════╣\n";
    std::cout << "  ║         操 作 说 明              ║\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ║  W/S/A/D  或  方向键  —  移动    ║\n";
    std::cout << "  ║  J                 —  发射子弹   ║\n";
    std::cout << "  ║  ESC               —  退出游戏   ║\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ╚══════════════════════════════════╝\n";
    std::cout << "\n        按任意键开始游戏...\n";
    _getch();
}
void Game::fireBullet()
{
    if (main_player.tryfire())
    {
        main_bullets.push_back(std::unique_ptr<Entity>(new Bullet(main_player.getX(), main_player.getY() - 1)));
    }
}
void Game::updateEntities()
{
    main_player.update();
    if (frame_counter % ENEMY_SPEED == 0)
    {
        for (auto &enemy : main_enemies)
            enemy->update();
    }
    /*  // 老式迭代器写法
for (vector<Enemy*>::iterator it = main_enemies.begin(); it != main_enemies.end(); ++it) {
    (*it)->update();
}*/
    for (auto &bullet : main_bullets)
    {
        bullet->update();
    }
}
void Game::checkCollisions()
{
    for (auto &bullet : main_bullets)
    {
        if (!bullet->isAlive())
        {
            continue;
        }
        for (auto &enemy : main_enemies)
        {
            if (!enemy->isAlive())
            {
                continue;
            }
            if (bullet->collidesWith(*enemy))
            {
                bullet->setAlive(false);
                enemy->setAlive(false);
                main_score += 10;
                break;
            }
        }
    }
    for (auto &enemy : main_enemies)
    {
        if (enemy->isAlive() && enemy->collidesWith(main_player))
        {
            if_running = false;
            return;
        }
    }
}
void Game::removeEntities()
{
    for (auto it = main_enemies.begin(); it != main_enemies.end();)
    {
        if (!(*it)->isAlive())
        {
            it = main_enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = main_bullets.begin(); it != main_bullets.end();)
    {
        if (!(*it)->isAlive())
        {
            it = main_bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
// 渲染
void Game::renderEntities()
{
    // 创建空白画布
    std::vector<std::string> buffer(HEIGHT, std::string(WIDTH, ' '));
    for (const auto &enemy : main_enemies)
        enemy->draw(buffer);
    for (const auto &bullet : main_bullets)
        bullet->draw(buffer);
    main_player.draw(buffer);
    setCursorPosition(0, 0);
    std::cout << "  ╔" << std::string(WIDTH, '=') << "╗\n";
    for (const auto &row : buffer)
        std::cout << "  ║" << row << "║\n";
    std::cout << "  ╚" << std::string(WIDTH, '=') << "╝\n";

    // 状态栏
    std::cout << "   得分: " << main_score
              << "    敌机: " << main_enemies.size()
              << "    [WASD/方向键:移动  J:射击  ESC:退出]\n";
}
bool Game::showGameOverScreen()
{
    clearScreen();
    std::cout << "\n\n";
    std::cout << "  ╔══════════════════════════════════╗\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ║          G A M E   O V E R       ║\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ╠══════════════════════════════════╣\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ║         最终得分: " << main_score;

    // 算分数位数，补空格保持对齐
    int d = 0, t = (main_score == 0 ? 1 : main_score);
    while (t > 0)
    {
        d++;
        t /= 10;
    }
    for (int i = d; i < 8; i++)
        std::cout << " ";

    std::cout << " ║\n";
    std::cout << "  ║                                  ║\n";
    std::cout << "  ╠══════════════════════════════════╣\n";
    std::cout << "  ║  按 ESC 退出   按其他键重新开始    ║\n";
    std::cout << "  ╚══════════════════════════════════╝\n";
    int ch = _getch();
    if (ch == 224)
        _getch();
    return (ch != 27);
}
void Game::clearScreen()
{
    system("cls");
}
void Game::setCursorPosition(int x, int y)
{
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Game::hideCursor()
{
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
    ci.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}
void Game::showCursor()
{
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
    ci.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}