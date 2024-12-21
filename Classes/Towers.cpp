
#include "Towers.h"
#include "tools.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"
#define NULL 0
USING_NS_CC;
using namespace ui;
using namespace std;

/* 创建防御塔 */
Tower* Tower::create_Tower(int type, int line, int row, Scene* scene)
{
    Vec2 pos = get_po(line, row);
    auto building = Tower::create();
    building->setType(towers[type]);
    building->base = Sprite::create();
    building->bullet = Sprite::create();
    building->_setScale(1.5, 1.5, 1.5);
    building->_setPosition(pos);
    building->_setSpriteFrame();
    scene->addChild(building, 3);
    scene->addChild(building->base, 2);
    scene->addChild(building->bullet, -10);

    return building;
}

void Tower::_setPosition(const Vec2& pos)
{
    this->setPosition(pos);
    this->base->setPosition(pos);
    this->bullet->setPosition(pos);
}

void Tower::_setSpriteFrame() {
    this->setSpriteFrame(this->info.origin_url[this->level]);
    this->base->setSpriteFrame(this->info.D[this->level]);
    this->bullet->setSpriteFrame(this->info.bullet_url[this->level]);
}

void Tower::_setScale(const float& building_scale, const float& base_scale, const float& bullet_scale) {
    this->setScale(building_scale);
    this->base->setScale(base_scale);
    this->bullet->setScale(bullet_scale);
}

void Tower::up_level() {
    level++;
    this->setSpriteFrame(this->info.origin_url[level]);
    this->base->setSpriteFrame(this->info.D[level]);
    this->bullet->setSpriteFrame(this->info.bullet_url[level]);
}

int Tower::tower_rotate_direction() {
    Monster* mon = this->get_first_monster();
    if (mon == nullptr)
        return 0;//不旋转

    Vec2 po1 = this->getPosition();
    Vec2 po2 = mon->getPosition();

    float mon_angle = cal_relative_angle(po1, po2);
    float tower_angle = this->get_angle();

    //return mon_angle;
    /* 判断旋转方向 */
    if (fabs(mon_angle - tower_angle) <= 3)
        return 0;//不旋转

    int clock_wise = 0;//顺时针为1 逆时针为-1

    if (mon_angle >= 0 && mon_angle <= 180) {
        if (tower_angle >= mon_angle && tower_angle <= mon_angle + 180)
            clock_wise = 3;
        else
            clock_wise = -3;
    }
    else {
        if (tower_angle >= mon_angle - 180 && tower_angle <= mon_angle)
            clock_wise = -3;
        else
            clock_wise = 3;
    }

    return -clock_wise;//逆时针为正方向
}

Monster* Tower::get_first_monster() {
    auto s = Director::getInstance()->getRunningScene();
    Map_1_01* scene = static_cast<Map_1_01*>(s);
    /* 抓取所有怪物 */
    Monster* mons[20];
    int cur_tag = scene->get_mons_tag();
    int least = 10101, co = 0;
    update_tag(least, scene->get_waves());
    while (cur_tag >= least)
        mons[co++] = scene->getChildByTag<Monster*>(least++);

    Vec2 tower_po = this->getPosition();//防御塔位置

    for (int i = 0; i < co; i++)
    {
        if (!mons[i])
            continue;
        Vec2 mons_po = mons[i]->getPosition();
        //算距离
        float distance = cal_distance(tower_po, mons_po);
        if (distance <= this->get_range())
            return mons[i];
    }

    return NULL;
}

void Tower::tower_rotate_1(float dt) {
    int direc = tower_rotate_direction();//逆时针为正方向
    if (direc == 0)
        return;
    float de = direc - angle;
    float change = 0;
    //if (de > 180)
    //    change = 3;
    //else if (de <= 180 && de > 3)
    //    change = -3;
    //else if (de <= 3 && de >= -3)
    //    change = -de;
    //else if (de < -3 && de >= -180)
    //    change = 3;
    //else if (de < -180)
    //    change = -3;
    float change_angle = 2.0f * direc;
    float next_ag = angle + change_angle;
    //float next_ag = angle + change;

    if (next_ag >= 360)
        next_ag -= 360;
    else if (next_ag < 0)
        next_ag += 360;
    angle = next_ag;

    this->setRotation(next_ag);
    this->bullet->setRotation(next_ag);
    //this->setRotation(change_angle);
    //this->bullet->setRotation(change_angle);
}

void Tower::shoot_3(float dt) {//风扇 0.4s 2格     5/60=1/12 格   每1/60s
    Monster* mon = this->get_first_monster();
    if (!mon)
        return;
    Vec2 po1 = this->getPosition();//子弹起始坐标
    Vec2 po2 = mon->getPosition();//怪物坐标
    //向量 子弹指向怪物
    float x = po2.x - po1.x;//向量x方向
    float y = po2.y - po1.y;//向量y方向

    float d = cal_distance(po1, po2);//向量长度

    float beilv = 1.0f / 12 * 95 / d;//现在要求1/60s走多长 先求倍率 即beilv*d=1/150*95
    this->biu_fan(po1, x * beilv, y * beilv);
}

void Tower::biu_fan(Vec2& start, float x, float y) {
    auto biu = Sprite::create();
    biu->setPosition(start);
    biu->setScale(1.5);
    biu->setSpriteFrame(this->get_bullet_url());
    auto scene = Director::getInstance()->getRunningScene();
    scene->addChild(biu, 4);
    auto rotate = RotateBy::create(1.0f / 60, 30.0f);
    auto ahead = MoveBy::create(1.0f / 60, Vec2(x, y));
    //auto delay = DelayTime::create(0.2f);
    auto call_check = CallFunc::create([biu = biu]() {
        Vec2 cur_pos = biu->getPosition();
        if (cur_pos.x >= 1380 || cur_pos.x <= 240 || cur_pos.y >= 860 || cur_pos.y <= 100)
            biu->removeFromParentAndCleanup(true);
        });
    //auto seq = Sequence::create(delay, call_check, nullptr);
    //auto spawn = Spawn::create(rotate, ahead, seq, nullptr);
    auto spawn = Spawn::create(rotate, ahead, call_check, nullptr);

    auto repeat = RepeatForever::create(spawn);
    biu->runAction(repeat);

}

/* 怪物初始化 */
bool Tower::init()
{
    if (!Sprite::init())
        return false;





    return true;
}