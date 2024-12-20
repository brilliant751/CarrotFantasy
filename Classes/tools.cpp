#include "cocos2d.h"
#include "ui/cocosGUI.h"
using namespace std;
USING_NS_CC;
using namespace ui;

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
    tag += waves * 100;
    tag -= tag % 100;
    ++tag;
}

/* 创建精灵 */
    //pctname：  图集中的名称
    //pos：      坐标
    //scale：    放大倍率
    //layer：    放置层数
Sprite* sp_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0)
{
    Sprite* newsp = Sprite::create();
    newsp->initWithSpriteFrameName(pctname);
    newsp->setPosition(pos);
    newsp->setScale(scale);
    parent->addChild(newsp, layer);
    return newsp;
};

/* 创建按钮的闭包函数 */
//lambda表达式
//normal：   正常状态显示
//pressed：  点击状态显示
//pos：      坐标
//scale：    放大倍率
//layer：    放置层数
Button* btn_create(Scene* parent,const string& normal, const string& pressed,
    const Vec2& pos, const float& scale, int layer)
    {
        auto btn = Button::create();
        btn->loadTextures(normal, pressed, normal);
        btn->setPosition(pos);
        btn->setScale(scale);
        parent->addChild(btn, layer);
        return btn;
    };

/* 创建标签 */
// 整数类型重载
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
};

/* 创建标签 */
// 字符串类型重载
Label* lb_create(Scene* parent, const string text, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0)
{
    auto myLabel = Label::createWithTTF(text, ttf, size);
    myLabel->setPosition(pos);
    myLabel->enableBold();
    if (color == 1)
        myLabel->setColor(Color3B(255, 246, 143));
    parent->addChild(myLabel, layer);
    return myLabel;
};
