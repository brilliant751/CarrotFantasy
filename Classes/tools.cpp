#include "cocos2d.h"
using namespace std;
USING_NS_CC;

const Vec2 origin = Vec2(240, 100); //��ͼ�������

// ��ȡline row����������
Vec2 get_po(int line, int row)
{
    float x = origin.x + (0.5 + row) * 95;
    float y = origin.y + (7.5 - line) * 95;
    return Vec2(x, y);
}

// ��ȡ������
int get_line(float y)
{
    return round(7.5 - (y - origin.y) / 95);
}

// ��ȡ������
int get_row(float x)
{
    return round((x - origin.x) / 95 - 0.5);
}

// ��ȡ����
int get_tag_waves(int tag)
{
    return tag / 100 % 100;
}

// ���²���
void update_tag(int& tag, int waves)
{
    tag -= get_tag_waves(tag) * 100;
    tag -= tag % 100;
    ++tag;
    tag += waves * 100;
}