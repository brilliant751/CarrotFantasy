#include "cocos2d.h"
using namespace std;
USING_NS_CC;

const Vec2 origin = Vec2(240, 100); //地图坐标起点

//获取line row的中心位置
Vec2 get_po(int line, int row) {
    float x = origin.x + (0.5 + row) * 95;
    float y = origin.y + (7.5 - line) * 95;
    return Vec2(x, y);
}

int get_line(float y) {
    return round(7.5 - (y - origin.y) / 95);
}

int get_row(float x) {
    return round((x - origin.x) / 95 - 0.5);
}