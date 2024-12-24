
#include "Monsters.h"
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "Carrot.h"
#include "tools.h"


USING_NS_CC;
using namespace ui;
using namespace std;

extern int speed;
extern bool is_stop;
extern clock_t timer;
extern int waves;
extern Target* target;
extern Monster* cur_mons[20];   //当前所有怪物
extern int lives;      //栈顶指针，当前场上怪物数量

/* 更新怪物坐标 */
void Monster::update(float dt)
{
    if (is_stop)
        return; //暂停时不移动
    /* 到达萝卜 */
    if (rt == top)
    {
        auto sp = Director::getInstance()->getRunningScene()->getChildByName<Carrot*>("carrot");
        sp->cut_chp();       
        this->unscheduleUpdate();
        auto tag = this->getTag();
        if (target == this)
            target = NULL;
        this->selected->removeFromParentAndCleanup(true);
        this->hp_holder->removeFromParentAndCleanup(true);
        this->hp_slider->removeFromParentAndCleanup(true);
        this->removeFromParentAndCleanup(true);
        cur_mons[tag % 100 - 1] = NULL;
        return;
    }
    Vec2 cur = getPosition();   //获取当前位置
    Vec2 hp_pos = hp_slider->getPosition(); //获取血条位置
    Vec2 ex_pos = cur;      //记录当前位置
    /* 计算坐标变化 */
    if (cur.x < route[rt].x)
    {
        if (cur.x + info.speed * speed * sp_percent > route[rt].x)
            cur.x = route[rt].x;
        else
            cur.x += info.speed * speed * sp_percent;
    }
    else if (cur.x > route[rt].x)
    {
        if (cur.x - info.speed * speed * sp_percent < route[rt].x)
            cur.x = route[rt].x;
        else
            cur.x -= info.speed * speed * sp_percent;
    }
    else if (cur.y < route[rt].y)
    {
        if (cur.y + info.speed * speed * sp_percent > route[rt].y)
            cur.y = route[rt].y;
        else
            cur.y += info.speed * speed * sp_percent;
    }
    else if (cur.y > route[rt].y)
    {
        if (cur.y - info.speed * speed * sp_percent < route[rt].y)
            cur.y = route[rt].y;
        else
            cur.y -= info.speed * speed * sp_percent;
    }
    else
        ++rt;   //靠近下一个拐点
    /* 更新血条位置 */
    update_pos(hp_pos, ex_pos, cur);
    hp_slider->setPosition(hp_pos);
    hp_holder->setPosition(hp_pos);
    // 更新锁定标记位置
    selected->setPosition(hp_pos);
    // 更新怪物位置
    setPosition(cur);
}

/* 怪物初始化 */
bool Monster::init()
{
	if (!Sprite::init())
		return false;
    reward = 20;
	return true;
}

/* 创建怪物 */
Monster* Monster::create_Monster(monf type, const Vec2* path, const int& top)
{
    auto scene = Director::getInstance()->getRunningScene();
    auto mt = Monster::create();
    mt->setType(type);      //设置怪物类型
    mt->setHP(mt->info.hp * waves);     //设置血量（随波次变化）
    mt->set_route(path, top);           //设置路线
    mt->setPosition(mt->route[0]);      //设置位置（路线起始点）
    mt->setScale(1.5f);     //设置放大倍率
    mt->setAnchorPoint(Vec2(0.5, 0));   //设置锚点为脚部
    mt->scheduleUpdate();               //实现按路径移动
    mt->create_slider();                //创建血条
    return mt;
}

/* 创建血条 */
void Monster::create_slider()
{
    auto scene = Director::getInstance()->getRunningScene();
    Vec2 pos = Vec2(route[0].x, route[0].y + 100);
    hp_slider = LoadingBar::create();
    hp_slider->loadTexture("Monsters/contents/hp_slider.png");
    hp_slider->setScale(1.5f);
    hp_slider->setPercent(100.0f);
    hp_slider->setPosition(pos);
    hp_slider->setAnchorPoint(Vec2(0.5f, 1.0f));
    scene->addChild(hp_slider, 4);
    hp_holder = sp_create(scene, "hp_holder.png", pos, 1.5f, 3);
    hp_holder->setAnchorPoint(Vec2(0.5f, 1.0f));
    selected = sp_create(scene, "selected.png", pos, 1.5f, -5);
    selected->setAnchorPoint(Vec2(0.5f, 0.0f));
}

/* 设置移动速率 */
void Monster::set_sp_percent(float percent, float duration)
{
    auto set_func = CallFunc::create([this, percent = percent]() {
        auto act = this->getActionByTag(this->slow_tag - 1);    //获取上一个动作
        if (act != nullptr)
            this->stopAction(act);     //停止之前的减速动作
        this->sp_percent = 1.0f - percent;      //减速
        });
    auto delay = DelayTime::create(duration);
    auto end_func = CallFunc::create([this]() {
        this->sp_percent = 1.0f;        //恢复速率
        });
    auto seq = Sequence::create(set_func, delay, end_func, nullptr);
    seq->setTag(++slow_tag);
    runAction(seq);
}