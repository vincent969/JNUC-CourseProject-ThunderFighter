# 雷霆战机 (Thunder Fighter)

C++ 控制台飞机大战游戏 — 基于 C++11 的经典射击小游戏。

## 游戏截图

```
  ╔══════════════════════════════════╗
  ║                                  ║
  ║         雷霆战机                 ║
  ║         THUNDER FIGHTER          ║
  ║                                  ║
  ╠══════════════════════════════════╣
  ║         操 作 说 明              ║
  ║                                  ║
  ║  W/S/A/D  或  方向键  —  移动    ║
  ║  J                 —  发射子弹   ║
  ║  ESC               —  退出游戏   ║
  ║                                  ║
  ╚══════════════════════════════════╝
```

## 操作方式

| 按键 | 功能 |
|------|------|
| `W` / `↑` | 向上移动 |
| `S` / `↓` | 向下移动 |
| `A` / `←` | 向左移动 |
| `D` / `→` | 向右移动 |
| `J` | 发射子弹 |
| `ESC` | 退出游戏 |

## 编译运行

### 依赖

- C++11 或更高版本
- CMake 3.10+

### 使用 CMake 构建

```bash
mkdir build && cd build
cmake ..
cmake --build .
./flyfight
```

### 使用 g++ 直接编译

```bash
g++ -std=c++11 -Iinclude src/*.cpp -o flyfight
./flyfight
```

## 项目结构

```
flyfight/
├── include/           # 头文件
│   ├── Bullet.h       # 子弹类
│   ├── Constant.h     # 游戏常量配置
│   ├── Direction.h    # 方向枚举
│   ├── Enemy.h        # 敌机类
│   ├── Entity.h       # 实体基类
│   ├── Game.h         # 游戏主逻辑
│   └── Player.h       # 玩家类
├── src/               # 源文件
│   ├── main.cpp       # 入口
│   ├── Game.cpp       # 游戏循环与控制台渲染
│   ├── Entity.cpp     # 实体基类实现
│   ├── Player.cpp     # 玩家逻辑
│   ├── Enemy.cpp      # 敌机逻辑
│   └── Bullet.cpp     # 子弹逻辑
└── CMakeLists.txt     # CMake 构建配置
```

## 设计说明

- 面向对象设计：`Entity` 抽象基类，`Player`/`Enemy`/`Bullet` 继承实现
- 游戏循环：输入处理 → 实体更新 → 碰撞检测 → 渲染
- 使用 `std::unique_ptr` 管理实体生命周期
- 双缓冲渲染，避免画面闪烁

## 课程项目

