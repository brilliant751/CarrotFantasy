
#include "Carrot.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"
#include "tools.h"


USING_NS_CC;
using namespace ui;
using namespace std;

Carrot* Carrot::create_Carrot(const Vec2& carrot_pos, Scene* scene) {
    auto carrot = Carrot::create();
	carrot->chp_bg = Sprite::create();
    carrot->c_pos.x=carrot_pos.x;
    carrot->c_pos.y = carrot_pos.y;
    const Vec2 chp_pos (carrot_pos.x + 80,carrot_pos.y - 10);
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
   c_hp--;
   const Vec2 chp_num_pos(c_pos.x + 93,c_pos.y - 10);//萝卜血条数字位置
   this->_setSpriteFrame(chp_url[c_hp-1]);
   auto scene = Director::getInstance()->getRunningScene();
   chp_num->setZOrder(-3);
   chp_num=lb_create(scene, c_hp, "fonts/HPSimplified_Bd.ttf", 27, chp_num_pos, 2);


}
/* 萝卜初始化 */
bool Carrot::init()
{
    if (!Sprite::init())
        return false;





    return true;
}