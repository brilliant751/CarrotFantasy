#include "cocos2d.h"
using namespace std;
USING_NS_CC;

const Vec2 origin = Vec2(240, 100); //地图坐标起点

// 获取line row的中心坐标
Vec2 get_po(int line, int row)
{
    float x = origin.x + (0.5 + row) * 95;
    float y = origin.y + (7.5 - line) * 95;
    return Vec2(x, y);
}

// 获取数组行
int get_line(float y)
{
    return round(7.5 - (y - origin.y) / 95);
}

// 获取数组列
int get_row(float x)
{
    return round((x - origin.x) / 95 - 0.5);
}

// 获取波次
int get_tag_waves(int tag)
{
    return tag / 100 % 100;
}

// 更新波次
void update_tag(int& tag, int waves)
{
    tag -= get_tag_waves(tag) * 100;
    tag -= tag % 100;
    ++tag;
    tag += waves * 100;
}