#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include "GameMenu.h"
using namespace std;
USING_NS_CC;
using namespace ui;

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
    tag += waves * 100;
    tag -= tag % 100;
    ++tag;
}

Vec2 pos_check(const Vec2& ex, const Vec2& cur)
{
    float dx, dy;
    dx = cur.x - ex.x;
    dy = cur.y - ex.y;
    return Vec2{ dx, dy };
}

void update_pos(Vec2& pos, const Vec2& ex, const Vec2& cur)
{
    Vec2 delta = pos_check(ex, cur);
    pos.x += delta.x;
    pos.y += delta.y;
}

/* �������� */
    //pctname��  ͼ���е�����
    //pos��      ����
    //scale��    �Ŵ���
    //layer��    ���ò���
Sprite* sp_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0)
{
    Sprite* newsp = Sprite::create();
    newsp->initWithSpriteFrameName(pctname);
    newsp->setPosition(pos);
    newsp->setScale(scale);
    parent->addChild(newsp, layer);
    return newsp;
}

/* ������ť�ıհ����� */
//lambda���ʽ
//normal��   ����״̬��ʾ
//pressed��  ���״̬��ʾ
//pos��      ����
//scale��    �Ŵ���
//layer��    ���ò���
Button* btn_create(Scene* parent, const string& normal, const string& pressed,
    const Vec2& pos, const float& scale, int layer)
{
    auto btn = Button::create();
    btn->loadTextures(normal, pressed, normal);
    btn->setPosition(pos);
    btn->setScale(scale);
    parent->addChild(btn, layer);
    return btn;
}

/* ������ǩ */
// ������������
Label* lb_create(Scene* parent, const int num, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0)
{
    string text = to_string(num);
    auto myLabel = Label::createWithTTF(text, ttf, size);
    myLabel->setPosition(pos);
    myLabel->enableBold();
    if (color == 1)
        myLabel->setColor(Color3B(255, 246, 143));
    else if (color == 2)
        myLabel->setColor(Color3B(157, 99, 13));

    parent->addChild(myLabel, layer);
    return myLabel;
}

/* ������ǩ */
// �ַ�����������
Label* lb_create(Scene* parent, const string text, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0)
{
    auto myLabel = Label::createWithTTF(text, ttf, size);
    myLabel->setPosition(pos);
    myLabel->enableBold();
    if (color == 1)
        myLabel->setColor(Color3B(255, 246, 143));
    parent->addChild(myLabel, layer);
    return myLabel;
}

/* �����ɹ������� */
    //pctname��  ͼ���е�����
    //pos��      ����
    //scale��    �Ŵ���
    //layer��    ���ò���
Target* targ_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.5f, int layer = 0)
{
    Target* newsp = Target::create();
    newsp->initWithSpriteFrameName(pctname);
    newsp->setPosition(pos);
    newsp->setScale(scale);
    parent->addChild(newsp, layer);
    newsp->create_slider();
    return newsp;
}

//�������
float cal_distance(const Vec2& po1, const Vec2& po2) {
    float x1 = po1.x, x2 = po2.x, y1 = po1.y, y2 = po2.y;
    float s_2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    float s = sqrt(s_2);
    return s;
}

//�������0��(-180��-> 180��)�ĽǶ�  po1������ po2���� ��������Ϊ������ָ����� 
float cal_relative_angle(const Vec2& po1, const Vec2& po2) {
    float x1 = po1.x, x2 = po2.x, y1 = po1.y, y2 = po2.y;
    float dx = x2 - x1, dy = y2 - y1;
    if (dx == 0)
        return (dy > 0 ? 90.0f : 270.0f);
    float vec_tan = dy / dx;
    float sim_angle = atan(vec_tan) / M_PI * 180;
    if (sim_angle < 0)
        sim_angle += 360;
    return sim_angle;
}