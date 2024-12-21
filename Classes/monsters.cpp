
#include "Monsters.h"
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "Carrot.h"


USING_NS_CC;
using namespace ui;
using namespace std;

extern int speed;
extern bool is_stop;
extern clock_t timer;
extern int waves;
extern Monster* cur_mons[20];   //当前所有怪物
extern int lives;      //栈顶指针，当前场上怪物数量

/* 创建怪物 */
Monster* Monster::create_Monster(monf type, const Vec2* path, const int& top)
{
    auto scene = Director::getInstance()->getRunningScene();
	auto mt = Monster::create();
	mt->setType(type);
    mt->setHP(mt->info.hp);
    mt->set_route(path, top);     //设置路线
    //mt->setSpriteFrame(mons_url[waves]);
    mt->setPosition(mt->route[0]);
    mt->setScale(1.5f);
    mt->setAnchorPoint(Vec2(0.5, 0)); //锚点为脚部
    //mt->setTag(mons_tag++);
    mt->scheduleUpdate(); //实现按路径移动
    auto hp_slider = LoadingBar::create();
    hp_slider->loadTexture("Monsters/hp_slider.png");
    hp_slider->setScale(1.5f);
    hp_slider->setPercent(100.0f);
    hp_slider->setPosition(Vec2(1000, 500));
    scene->addChild(hp_slider, 4);
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
        auto tag = this->getTag();
        this->removeFromParentAndCleanup(true);
        cur_mons[tag % 100 - 1] = NULL;
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
    // todo：更新血条位置
    setPosition(cur);
}

/* 怪物初始化 */
bool Monster::init()
{
	if (!Sprite::init())
		return false;





	return true;
}