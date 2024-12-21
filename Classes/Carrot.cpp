
#include "Carrot.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"
#include "tools.h"
#include"Skyline_01.h"
#include"Skyline_02.h"


USING_NS_CC;
using namespace ui;
using namespace std;

extern bool is_stop;
//创建弹窗层
Layer* PopCarrot::create_Layer()
{
    return PopCarrot::create();
}
bool PopCarrot::init() {
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620，960)

    /* 参数位置 */
    /*********************************/
    const Vec2 Pop(visibleSize / 2);     //失败/成功弹窗位置
    constexpr float btn_scale = 1.0f;       //按钮放大倍率
    const Vec2 again_btn(663, 370);          //again按钮
    const Vec2 chose_btn(903, 370);        //chose按钮
    /*********************************/

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/GameMenu/GameMenu.plist");
    auto main_scene = Director::getInstance()->getRunningScene();
    auto sp = Director::getInstance()->getRunningScene()->getChildByName<Carrot*>("carrot");

    /*********** 创建按钮 **********/
      /* 创建 再试一次 按钮 */
    auto again = btn_create(main_scene,
        "Levels/GameMenu/again_normal.png",
        "Levels/GameMenu/again_pressed.png",
        again_btn, btn_scale, 12);
    again->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->replaceScene(Map_1_01::create());
            break;
        default:
            break;
        }
        });

    /* 创建 选择关卡 按钮 */
    auto chose = btn_create(main_scene,
        "Levels/GameMenu/return_normal.png",
        "Levels/GameMenu/return_pressed.png",
        chose_btn, btn_scale, 12);
    chose->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
            break;
        default:
            break;
        }
        });



    /* 创建 失败弹窗 */
    auto lose = sp_create(main_scene, "lose_bg.png", Pop, 2.0f, 11);
    lose->setName("lose");


    return true;

}

Carrot* Carrot::create_Carrot(const Vec2& carrot_pos, Scene* scene) {
    auto carrot = Carrot::create();
    carrot->chp_bg = Sprite::create();
    carrot->c_pos.x = carrot_pos.x;
    carrot->c_pos.y = carrot_pos.y;
    const Vec2 chp_pos(carrot_pos.x + 80, carrot_pos.y - 10);
    const Vec2 chp_num_pos(carrot->c_pos.x + 93, carrot->c_pos.y - 10);
    carrot->chp_num = lb_create(scene, carrot->c_hp, "fonts/HPSimplified_Bd.ttf", 27, chp_num_pos, 2);
    carrot->chp_num->setName("chp_num");
    carrot->_setPosition(carrot_pos, chp_pos);
    carrot->_setScale(1.5, 1.5);
    carrot->_setSpriteFrame(carrot->chp_url[9]);
    carrot->chp_bg->setSpriteFrame("Hp.png");
    scene->addChild(carrot, 3);
    scene->addChild(carrot->chp_bg, 1);

    return carrot;
}
void Carrot::_setPosition(const Vec2& carrot_pos, const Vec2& chp_pos)
{
    this->setPosition(carrot_pos);
    this->chp_bg->setPosition(chp_pos);
}

void Carrot::_setSpriteFrame(const string& chp_url) {
    this->setSpriteFrame(chp_url);
}

void Carrot::_setScale(const float& carrot_scale, const float& chp_scale) {
    this->setScale(carrot_scale);
    this->chp_bg->setScale(chp_scale);
}
void Carrot::cut_chp() {
    if (c_hp > 1) {
        c_hp--;
        const Vec2 chp_num_pos(c_pos.x + 93, c_pos.y - 10);//萝卜血条数字位置
        this->_setSpriteFrame(chp_url[c_hp - 1]);
        auto scene = Director::getInstance()->getRunningScene();
        chp_num->setZOrder(-3);
        chp_num = lb_create(scene, c_hp, "fonts/HPSimplified_Bd.ttf", 27, chp_num_pos, 2);
    }
    else {
        auto lose_layer = PopCarrot::create_Layer();    //创建失败弹窗
        /* 创建调暗层 */
        auto dimlayer = LayerColor::create(Color4B(0, 0, 0, 128), 1620, 960);
        dimlayer->setName("dimmer");
        auto scene = Director::getInstance()->getRunningScene();
        scene->addChild(lose_layer, 10);
        scene->addChild(dimlayer, 9);
        /* 暂停主场景的活动 */
        // 此处会循环暂停所有child结点的监听事件
        scene->getEventDispatcher()->pauseEventListenersForTarget(this, true);
        // 暂停所有刷新和动作
        scene->pauseSchedulerAndActions();
        /* 恢复弹窗层的监听事件 */
        scene->getEventDispatcher()->resumeEventListenersForTarget(lose_layer, true);
        is_stop = true;     //标记暂停
    }


}

/* 萝卜初始化 */
bool Carrot::init()
{
    if (!Sprite::init())
        return false;





    return true;
}