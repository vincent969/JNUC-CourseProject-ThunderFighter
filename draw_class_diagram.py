"""
画类继承关系图，输出 class_diagram.png
"""
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch
import matplotlib.patches as mpatches

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'Noto Sans CJK SC', 'DejaVu Sans']
plt.rcParams['axes.unicode_minus'] = False

fig, ax = plt.subplots(1, 1, figsize=(12, 9))
ax.set_xlim(0, 12)
ax.set_ylim(0, 11)
ax.axis('off')
ax.set_facecolor('#FAFAFA')
fig.patch.set_facecolor('#FAFAFA')

def draw_box(ax, x, y, w, h, title, lines, color, edge_color, text_color='black', alpha=0.95):
    """画一个带标题和内容的圆角矩形"""
    box = FancyBboxPatch((x - w/2, y - h/2), w, h,
                          boxstyle="round,pad=0.15",
                          facecolor=color, edgecolor=edge_color,
                          linewidth=2, alpha=alpha)
    ax.add_patch(box)
    # 标题（粗体）
    ax.text(x, y + h/2 - 0.55, title, ha='center', va='top',
            fontsize=13, fontweight='bold', color=edge_color)
    # 分隔线
    ax.plot([x - w/2 + 0.2, x + w/2 - 0.2], [y + h/2 - 0.9, y + h/2 - 0.9],
            color=edge_color, linewidth=0.8)
    # 内容行
    for i, line in enumerate(lines):
        ax.text(x, y + h/2 - 1.15 - i * 0.55, line, ha='center', va='top',
                fontsize=10, color=text_color)

def draw_arrow(ax, x1, y1, x2, y2, style='solid', color='#555555'):
    """画箭头 from (x1,y1) to (x2,y2)"""
    ax.annotate('', xy=(x2, y2), xytext=(x1, y1),
                arrowprops=dict(arrowstyle='->', color=color, lw=2.2,
                                connectionstyle='arc3,rad=0',
                                linestyle=style))

def draw_dashed_arrow(ax, x1, y1, x2, y2, color='#888888'):
    """画虚线箭头（组合关系）"""
    ax.annotate('', xy=(x2, y2), xytext=(x1, y1),
                arrowprops=dict(arrowstyle='->', color=color, lw=1.5,
                                connectionstyle='arc3,rad=0',
                                linestyle='dashed'))

# ========== Entity 基类（顶部居中）==========
draw_box(ax, x=6, y=9, w=5.5, h=2.8,
         title='Entity（抽象基类）',
         lines=[
             '+ main_x, main_y : int      坐标',
             '+ main_symbol : char        显示符号',
             '+ main_alive : bool         存活状态',
             '──────────────────────────',
             '+ update() = 0             纯虚函数',
             '+ draw(buffer)             虚函数',
             '+ collidesWith(other)      碰撞检测',
         ],
         color='#E3F2FD', edge_color='#1565C0')

# ========== 三个派生类（中间排）==========
# Player 左侧
draw_box(ax, x=2, y=5.5, w=3.2, h=2.2,
         title='Player（玩家）',
         lines=[
             '- fireCooldown : int    冷却计时',
             '──────────────────────────',
             '+ move(dir)             移动',
             '+ tryFire() : bool       射击',
             '+ update() override',
         ],
         color='#E8F5E9', edge_color='#2E7D32')

# Enemy 中间
draw_box(ax, x=6, y=5.5, w=3.2, h=2.0,
         title='Enemy（敌机）',
         lines=[
             '显示符号: V',
             '──────────────────────────',
             '+ update() override      y++ 下移',
             '+ draw(buffer) override',
         ],
         color='#FFF3E0', edge_color='#E65100')

# Bullet 右侧
draw_box(ax, x=10, y=5.5, w=3.2, h=2.0,
         title='Bullet（子弹）',
         lines=[
             '显示符号: |',
             '──────────────────────────',
             '+ update() override      y-- 上飞',
             '+ draw(buffer) override',
         ],
         color='#FCE4EC', edge_color='#C62828')

# ========== Game 类（底部）==========
draw_box(ax, x=6, y=1.5, w=6.5, h=2.5,
         title='Game（游戏主控 — 组合关系）',
         lines=[
             '- player : Player',
             '- enemies : vector<unique_ptr<Entity>>',
             '- bullets : vector<unique_ptr<Entity>>',
             '- score : int    |  running : bool',
             '──────────────────────────',
             '+ run()                主循环',
             '+ handleInput()        输入处理',
             '+ spawnEnemies()       生成敌机',
             '+ renderEntities()     渲染',
         ],
         color='#F3E5F5', edge_color='#6A1B9A')

# ========== 画箭头 ==========
# Entity → Player（继承，实线）
draw_arrow(ax, 4.3, 7.8, 2.0, 6.5, style='solid', color='#1565C0')
# Entity → Enemy（继承，实线）
draw_arrow(ax, 6.0, 7.8, 6.0, 6.4, style='solid', color='#1565C0')
# Entity → Bullet（继承，实线）
draw_arrow(ax, 7.7, 7.8, 10.0, 6.5, style='solid', color='#1565C0')

# Game → Player / Enemy / Bullet（组合，虚线）
draw_dashed_arrow(ax, 3.5, 2.8, 2.0, 4.5, color='#6A1B9A')
draw_dashed_arrow(ax, 5.5, 2.8, 5.5, 4.5, color='#6A1B9A')
draw_dashed_arrow(ax, 8.5, 2.8, 10.0, 4.5, color='#6A1B9A')

# ========== 图例 ==========
legend_elements = [
    mpatches.FancyArrow(0, 0, 0.3, 0, color='#1565C0', lw=2.2,
                        label='继承 (extends)'),
    mpatches.FancyArrow(0, 0, 0.3, 0, color='#888888', lw=1.5,
                        linestyle='dashed', label='组合/使用 (has-a)'),
]
ax.legend(handles=legend_elements, loc='lower right', fontsize=11,
          framealpha=0.9, edgecolor='#CCCCCC')

# ========== 标注 ==========
ax.text(3.1, 7.35, 'extends', fontsize=9, color='#1565C0', fontstyle='italic',
        rotation=55, va='center')
ax.text(8.9, 7.35, 'extends', fontsize=9, color='#1565C0', fontstyle='italic',
        rotation=-55, va='center')
ax.text(4.5, 3.8, 'has-a', fontsize=9, color='#6A1B9A', fontstyle='italic',
        rotation=45, va='center')
ax.text(7.5, 3.8, 'has-a', fontsize=9, color='#6A1B9A', fontstyle='italic',
        rotation=-45, va='center')

plt.tight_layout(pad=0.5)
plt.savefig('class_diagram.png', dpi=200, bbox_inches='tight',
            facecolor='#FAFAFA', edgecolor='none')
print("Class diagram saved: class_diagram.png")
