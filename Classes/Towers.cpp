
#include "Towers.h"
#include "tools.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace ui;
using namespace std;

/* 创建防御塔 */
Tower* Tower::create_Tower(int type, int line,int row,Scene* scene)
{
    Vec2 building_pos = get_po(line, row);
    Vec2 base_pos = get_po(line, row);
    auto building = Tower::create();
    building->setType(towers[type]);
    building->base = Sprite::create();
    building->_setPosition(building_pos, base_pos);
    building->_setScale(1.5, 1.5);
    building->_setSpriteFrame(building->info.origin_url[building->level], building->info.D[building->level]);
    scene->addChild(building, 3);
    scene->addChild(building->base, 2);

    return building;
}

void Tower::_setPosition(const Vec2& building_pos,const Vec2& base_pos)
{
    this->setPosition(building_pos);
    this->base->setPosition(base_pos);
}

void Tower::_setSpriteFrame(const string& building_url, const string& base_url) {
    this->setSpriteFrame(building_url);
    this->base->setSpriteFrame(base_url);
}

void Tower::_setScale(const float& building_scale, const float& base_scale) {
    this->setScale(building_scale);
    this->base->setScale(base_scale);
}

void Tower::up_level() {
    level++;
    this->setSpriteFrame(this->info.origin_url[level]);
    this->base->setSpriteFrame(this->info.D[level]);
}

/* 怪物初始化 */
bool Tower::init()
{
    if (!Sprite::init())
        return false;





    return true;
}