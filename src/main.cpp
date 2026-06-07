#include "Game.h"
#include <cstdlib>   //提供rand函数
#include <ctime>     //提供time函数
#include <windows.h> //提供SetConsoleOutputCP函数
int main()
{
    srand(static_cast<unsigned>(time(nullptr))); // 随机生成种子
    SetConsoleOutputCP(CP_UTF8);                 // 设置控制台输出编码为utf-8,防止生成乱码
    Game game;
    game.run();
    return 0;
}
