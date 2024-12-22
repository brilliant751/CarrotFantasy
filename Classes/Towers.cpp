
#include "Towers.h"
#include "tools.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"
#define NULL 0
USING_NS_CC;
using namespace ui;
using namespace std;

extern int waves;   //怪物波次
extern int speed;   //游戏速度
extern Monster* cur_mons[20];   //场上怪物
extern int lives;   //场上怪物数量
extern Target* target;

/* 创建防御塔 */
Tower* Tower::create_Tower(int type, int line, int row, Scene* scene)
{
    Vec2 pos = get_po(line, row);
    auto building = Tower::create();
    building->setType(towers[type]);
    building->type = type;
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

/* 设置坐标 */
void Tower::_setPosition(const Vec2& pos)
{
    this->setPosition(pos);
    this->base->setPosition(pos);
    this->bullet->setPosition(pos);
}

/* 设置精灵图片 */
void Tower::_setSpriteFrame() {
    this->setSpriteFrame(this->info.origin_url[this->level]);
    this->base->setSpriteFrame(this->info.D[this->level]);
    this->bullet->setSpriteFrame(this->info.bullet_url[this->level]);
}

/* 设置放大倍率 */
void Tower::_setScale(const float& building_scale, const float& base_scale, const float& bullet_scale) {
    this->setScale(building_scale);
    this->base->setScale(base_scale);
    this->bullet->setScale(bullet_scale);
}

/* 炮塔升级 */
void Tower::up_level() {
    level++;
    if (this->type == 2) {
        this->unschedule(schedule_selector(Tower::shoot_3));
        this->schedule(schedule_selector(Tower::shoot_3), this->info.speed[level] / speed);
    }
    else {
        this->unschedule(schedule_selector(Tower::shoot_1_2));
        this->schedule(schedule_selector(Tower::shoot_1_2), this->info.speed[level] / speed);
    }
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

Monster* Tower::get_first_monster() {//获取范围内第一个Montser
    for (int i = 0; i < lives; ++i)
        if (cur_mons[i]) {
            float d = cal_distance(this->getPosition(), cur_mons[i]->getPosition());
            if (d <= this->info.radius[this->get_level()])
                return cur_mons[i];
        }
    return NULL;
}

void Tower::tower_rotate_1(float dt) {
    //int direc = tower_rotate_direction();//逆时针为正方向
    //if (direc == 0)
    //    return;
    //float de = direc - angle;
    //float change = 0;
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
    //float change_angle = 2.0f * direc;
    //float next_ag = angle + change_angle;
    ////float next_ag = angle + change;

    //if (next_ag >= 360)
    //    next_ag -= 360;
    //else if (next_ag < 0)
    //    next_ag += 360;
    //angle = next_ag;

    //this->setRotation(next_ag);
    //this->bullet->setRotation(next_ag);
    //this->setRotation(change_angle);
    //this->bullet->setRotation(change_angle);
}

void Tower::shoot_1_2(float dt) {
    Vec2 po1 = this->getPosition();//子弹起始坐标
    Target* mon = NULL;//Tower此时攻击对象
    if (target) {//先判断有没有选中对象以及是否在范围内
        float d = cal_distance(po1, target->getPosition());//计算距离
        if (d <= this->info.radius[this->get_level()])//在范围内
            mon = target;
        else //寻找在范围内的第一个怪物
            mon = this->get_first_monster();
    }
    else //寻找在范围内的第一个怪物
        mon = this->get_first_monster();
    if (!mon)//无怪物就不发射
        return;
    /* 有在范围内的怪物 发射子弹 旋转*/
    Vec2 po2 = mon->getPosition();
    float angle = -cal_relative_angle(po1, po2);
    if (this->get_type() == 0) {
        auto rotate = RotateTo::create(0.0f, angle);
        this->runAction(rotate);//拉倒 
    }
    this->biu_1_2(po1, mon->getTag(),angle);
}

void Tower::shoot_3(float dt) {//风扇 0.4s 2格     5/60=1/12 格   每1/60s
    Vec2 po1 = this->getPosition();//子弹起始坐标
    Target* mon = NULL;//Tower此时攻击对象
    if (target) {//先判断有没有选中对象以及是否在范围内
        float d = cal_distance(po1, target->getPosition());//计算距离
        if (d <= this->info.radius[this->get_level()])//在范围内
            mon = target;
        else //寻找在范围内的第一个怪物
            mon = this->get_first_monster();
    }
    else //寻找在范围内的第一个怪物
        mon = this->get_first_monster();
    if (!mon)//无怪物就不发射
        return;
    /* 有在范围内的怪物 发射子弹 */
    Vec2 po2 = mon->getPosition();//怪物坐标
    //向量 子弹指向怪物
    float x = po2.x - po1.x;//向量x方向
    float y = po2.y - po1.y;//向量y方向

    float d = cal_distance(po1, po2);//向量长度

    float beilv = 1.0f / 12 * 95 / d;//现在要求1/60s走多长 先求倍率 即beilv*d=1/150*95
    this->biu_fan(po1, x * beilv, y * beilv);
}

void Tower::biu_fan(Vec2& start, float x, float y) {
    /* 创建子弹 并初始化 */
    auto biu = Sprite::create();
    biu->setPosition(start);
    biu->setScale(1.5f);
    biu->setSpriteFrame(this->get_bullet_url());
    biu->setTag(0);
    auto scene = Director::getInstance()->getRunningScene();
    scene->addChild(biu, 4);
    auto rotate = RotateBy::create(1.0f / 60, 30.0f);
    auto ahead = MoveBy::create(1.0f / 60, Vec2(x, y));
    //auto delay = DelayTime::create(0.2f);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 10; j++)
            attacked[i][j] = 0; 
    auto call_check = CallFunc::create([this,scene=scene, biu = biu]() {
        Vec2 cur_pos = biu->getPosition();
        for (int i = 0; i < lives; i++)
            if (cur_mons[i] && cur_mons[i]->getBoundingBox().containsPoint(cur_pos) && !attacked[0][i]) {
                cur_mons[i]->get_hurt(this->get_info().attack[this->get_level()]);
                attacked[0][i] = 1;
            }
        for (int i = 0; i < 10; i++) {
            auto sp = scene->getChildByTag<Target*>(300001 + i);
            if (sp && sp->getBoundingBox().containsPoint(cur_pos) && !attacked[1][i]) {
                sp->get_hurt(this->get_info().attack[this->get_level()]);
                attacked[1][i] = 1;
            }
        }
        if (cur_pos.x >= 1380 || cur_pos.x <= 240 || cur_pos.y >= 860 || cur_pos.y <= 100)
            biu->removeFromParentAndCleanup(true);
        });
    //auto seq = Sequence::create(delay, call_check, nullptr);
    //auto spawn = Spawn::create(rotate, ahead, seq, nullptr);
    auto spawn = Spawn::create(rotate, ahead, call_check, nullptr);

    auto repeat = RepeatForever::create(spawn);
    biu->runAction(repeat);
}

// bottle shit子弹发射起始位置(Tower位置) 发射对象
void Tower::biu_1_2(Vec2& start, const int tag, float angle) {
    /* 实时变换方向的子弹发射 */
    //创建并初始化
    auto biu = Sprite::create();
    biu->setPosition(start);
    biu->setScale(1.5f);
    biu->setSpriteFrame(this->get_bullet_url());
    auto scene = Director::getInstance()->getRunningScene();
    
    auto rotate = RotateTo::create(0.0f, this->get_type() == 0 ? angle : angle - 180);
    biu->runAction(rotate);
    scene->addChild(biu, 2);

    float slow = this->get_info().slow_down[this->get_level()];//减速百分比
    float duration = this->get_info().duration[this->get_level()];//减速持续时间
    float attack = this->get_info().attack[this->get_level()];//伤害
    int tower_type = this->get_type();
    //this, scene = scene, biu = biu, tag = tag,slow=slow,duration=duration,tower_type=tower_type
    auto call_check = CallFunc::create([=]() {
        Vec2 po1 = biu->getPosition();
        auto p = scene->getChildByTag<Monster*>(tag);
        if (!p) {//发射目标在子弹到达前挂掉了or本来就不存在
            biu->removeFromParentAndCleanup(true);//子弹原地消失
            return;
        }
        else if (p->getBoundingBox().containsPoint(po1)) {//子弹到达发射目标
            if (tower_type == 1 && p->get_type() == 1) //shit 减速 怪物
                p->set_sp_percent(slow,duration);
            p->get_hurt(attack);//伤害
            //动画效果todo
            biu->removeFromParentAndCleanup(true);//消失
            return;
        }
        //先不管角度了
        // 子弹还没到达且发射目标存在
        //向量 子弹指向怪物
        int target_type = p->get_type();//获取目标类型 便于瞄准

        Vec2 po2 = p->getPosition();
        float x = po2.x - po1.x;//向量x方向
        float y = po2.y - po1.y + 40 * target_type;//向量y方向

        float d = cal_distance(po1, po2);//向量长度

        float beilv = 1.0f / 8 * 95 / d;//现在要求1/60s走多长 先求倍率 即beilv*d=1/150*95
        auto ahead = MoveBy::create(1.0f / 60, Vec2(x * beilv, y * beilv));//一帧的运动
        biu->runAction(ahead);//执行
        });

    //auto del
    auto delay = DelayTime::create(1.5f / 60);
    auto seq = Sequence::create(call_check, delay, nullptr);
    auto repeat = RepeatForever::create(seq);
    biu->runAction(repeat);

}

/* 怪物初始化 */
bool Tower::init()
{
    if (!Sprite::init())
        return false;
    return true;
}