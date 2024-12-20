
#include "monsters.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"
#include"Carrot.h"


USING_NS_CC;
using namespace ui;
using namespace std;

/* 创建怪物 */
Monster* Monster::create_Monster(monf type)
{
	auto mt = Monster::create();
	mt->setType(type);
    mt->setHP(mt->info.hp);
	return mt;
}

void Monster::update(float dt)
{
    if (is_stop)
        return;
    if (rt == top)
    {
        auto sp = Director::getInstance()->getRunningScene()->getChildByName<Carrot*>("carrot");
        sp->cut_chp();       
        this->unscheduleUpdate();
        this->removeFromParentAndCleanup(true);
        return;
    }
    Vec2 cur;
    cur = getPosition();
    if (cur.x < route[rt].x)
    {
        if (cur.x + info.speed * speed > route[rt].x)
            cur.x = route[rt].x;
        else
            cur.x += info.speed * speed;
    }
    else if (cur.x > route[rt].x)
    {
        if (cur.x - info.speed * speed < route[rt].x)
            cur.x = route[rt].x;
        else
            cur.x -= info.speed * speed;
    }
    else if (cur.y < route[rt].y)
    {
        if (cur.y + info.speed * speed > route[rt].y)
            cur.y = route[rt].y;
        else
            cur.y += info.speed * speed;
    }
    else if (cur.y > route[rt].y)
    {
        if (cur.y - info.speed * speed < route[rt].y)
            cur.y = route[rt].y;
        else
            cur.y -= info.speed * speed;
    }
    else
        ++rt;
    setPosition(cur);
}

/* 怪物初始化 */
bool Monster::init()
{
	if (!Sprite::init())
		return false;





	return true;
}