
#include "GameMenu.h"
#include "Skyline_01.h"
#include "Skyline_02.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;
using namespace ui;
using namespace std;

extern bool is_stop;    //标记游戏是否暂停
extern Target* target;

/* 创建Layer */
Layer* PauseMenu::create_Layer()
{
    return PauseMenu::create();
}

Layer* CountDown::create_Layer()
{
    return CountDown::create();
}

/* 初始化 */
bool PauseMenu::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(2050，1200)

    /* 创建精灵的闭包函数 */
    //lambda表达式
    //pctname：  图集中的名称
    //pos：      坐标
    //scale：    放大倍率
    //layer：    放置层数
    auto sp_create = [&](const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0) {
        Sprite* newsp = Sprite::create();
        newsp->initWithSpriteFrameName(pctname);
        newsp->setPosition(pos);
        newsp->setScale(scale);
        this->addChild(newsp, layer);
        return newsp;
        };

    /* 创建按钮的闭包函数 */
    //lambda表达式
    //normal：   正常状态显示
    //pressed：  点击状态显示
    //pos：      坐标
    //scale：    放大倍率
    //layer：    放置层数
    auto btn_create = [&](const string& normal, const string& pressed,
        const Vec2& pos, const float& scale = 1.0f, int layer = 1)
        {
            auto btn = Button::create();
            btn->loadTextures(normal, pressed, normal);
            btn->setPosition(pos);
            btn->setScale(scale);
            this->addChild(btn, layer);
            return btn;
        };

    /************     参数     ************/

    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;       //地图放大倍率
    constexpr float word_scale = 2.0f;      //文字放大倍率
    const Vec2 bg(visibleSize / 2);         //窗口位置
    const Vec2 ctn(796, 607);              //继续按钮位置
    const Vec2 rst(796, 495);              //继续按钮位置
    const Vec2 bck(796, 383);              //继续按钮位置

    /**************************************/

    /*********** 创建精灵 **********/
    /* 创建窗口背景 */
    auto menu_bg = sp_create("options_bg.png", bg, map_scale, -1);


    /*********** 创建按钮 **********/
    /* 创建 继续游戏 按钮 */
    auto resume = btn_create(
        "Levels/btn/continue_normal.png",
        "Levels/btn/continue_pressed.png",
        ctn, btn_scale, 1);
    resume->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                main_scene->removeChildByName("dimmer");    //除去调暗层
                main_scene->removeChild(this);      //关闭弹窗
                // 恢复主场景的监听事件
                main_scene->getEventDispatcher()->resumeEventListenersForTarget(main_scene, true);
                // 恢复主场景的刷新和动作
                main_scene->resumeSchedulerAndActions();
                is_stop = false;    //标记开始
                break;
            default:
                break;
        }
        });

    /* 创建 重新开始 按钮 */
    auto restart = btn_create(
        "Levels/btn/restart_normal.png",
        "Levels/btn/restart_pressed.png",
        rst, btn_scale, 1);
    restart->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                main_scene->removeChildByName("dimmer");    //除去调暗层
                main_scene->removeChild(this);      //关闭弹窗
                //todo:重新开始 
                /* 恢复主场景的监听事件 */
                main_scene->getEventDispatcher()->resumeEventListenersForTarget(main_scene, true);
                break;
            default:
                break;
        }
        });
    
    /* 创建 选择关卡 按钮 */
    auto back = btn_create(
        "Levels/btn/return_normal.png",
        "Levels/btn/return_pressed.png",
        bck, btn_scale, 1);
    back->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:      
                /* 返回MapChoose */
                Director::getInstance()->popScene();
                break;
            default:
                break;
        }
        });
    return true;
}

/* 初始化 */
bool CountDown::init() {
    if (!Layer::init())
        return false;

    /* 初始化局部变量 */
    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)
    const Vec2 po = (visibleSize / 2);  //倒计时位置
    const float scale = 1.5f;       //放大倍率

    //数字url
    string count_url[3] = {
        "start_time_1.png","start_time_2.png","start_time_3.png"
    };

    /* 创建精灵的闭包函数 */
    //lambda表达式
    //pctname：  图集中的名称
    //pos：      坐标
    //scale：    放大倍率
    //layer：    放置层数
    auto sp_create = [&](const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0) {
        Sprite* newsp = Sprite::create();
        newsp->initWithSpriteFrameName(pctname);
        newsp->setPosition(pos);
        newsp->setScale(scale);
        this->addChild(newsp, layer);
        return newsp;
        };
    
    /*********** 创建精灵 **********/
    /* 创建底板 */
    auto back = sp_create("start_time_bg.png", po, scale, 0);
    /* 创建圈圈 */
    auto lightning = sp_create("start_lightning.png", po, scale, 1);
    lightning->setAnchorPoint(Vec2(0.5, 0.5));
    /* 创建数字 */
    count = sp_create(count_url[co], po, scale, 1);
    count->setName("count");

    /*********** 创建动作 **********/
    /* 转圈圈 */
    auto roll = Sequence::create(RotateBy::create(3.0f, -1080.0f),nullptr);
    lightning->runAction(roll);
    /* 倒计时 */
    auto delay = DelayTime::create(0.8f);   //停留
    auto scaleTo = ScaleTo::create(0.2f, 0.0f);     //变小
    auto scaleBack = ScaleTo::create(0.01f, 1.0f);  //变大
    // 切换数字
    auto change = CallFunc::create([this]() {
        auto sp = (Sprite*)(this->getChildByName("count"));
        if (co >= 1) {
            co--;
            sp->setSpriteFrame(this->count_url[co]);
            auto scaleTo = ScaleTo::create(1.0f, 0.0f);           
        }
        else 
            Director::getInstance()->getRunningScene()->removeChild(this);
        });
    // 一次切换
    auto action_sequence = Sequence::create(delay,scaleTo, change, scaleBack, nullptr);
    // 重复三次
    auto rep = Repeat::create(action_sequence, 3);
    // 控制主场景
    auto ban = CallFunc::create([]() {
        /* 暂停主场景的活动 */
        auto cur_scene = Director::getInstance()->getRunningScene();
        // 此处会循环暂停所有child结点的监听事件
        cur_scene->getEventDispatcher()->pauseEventListenersForTarget(cur_scene, true);
        // 暂停主场景的刷新和动作
        cur_scene->pauseSchedulerAndActions();
        is_stop = true;     //标记暂停
        });
    auto resume= CallFunc::create([]() {
        /* 恢复主场景的活动 */
        auto cur_scene = Director::getInstance()->getRunningScene();
        // 此处会循环恢复所有child结点的监听事件
        cur_scene->getEventDispatcher()->resumeEventListenersForTarget(cur_scene, true);
        // 暂停主场景的刷新和动作
        cur_scene->resumeSchedulerAndActions();
        is_stop = false;    // 标记开始
        });
    // 整个动作
    auto all_sequence = Sequence::create(ban, rep, resume, nullptr);
    // 运行
    count->runAction(all_sequence);

    return true;
}

/* 创建血条 */
void Target::create_slider()
{
    auto scene = (Scene*)getParent();
    Vec2 pos = this->getPosition();
    pos.y += 70;
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

void Target::get_hurt(int damage)
{
    hp -= damage;
    float percent = hp / max_hp * 100;
    if (hp <= 0)
    {
        extern int money;
        extern Monster* cur_mons[20];
        money += reward;;	//奖励金钱
        if (get_type()) {
            cur_mons[this->getTag() % 100 - 1] = NULL;
            AudioEngine::play2d("sound/monster0.mp3", false);
        }
        if (target == this)
            target = NULL;
        this->selected->removeFromParentAndCleanup(true);
        this->hp_slider->removeFromParentAndCleanup(true);
        this->hp_holder->removeFromParentAndCleanup(true);
        this->removeFromParentAndCleanup(true);
        return;
    }
    hp_slider->setPercent(percent);
}
