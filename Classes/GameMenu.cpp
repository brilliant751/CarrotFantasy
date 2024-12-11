
#include "GameMenu.h"
#include "Skyline_01.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* ����Layer */
Layer* PauseMenu::create_Layer()
{
    return PauseMenu::create();
}

/* ��ʼ�� */
bool PauseMenu::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(2050��1200)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/GameMenu/GameMenu.plist");

    /* ��������ıհ����� */
    //lambda���ʽ
    //pctname��  ͼ���е�����
    //pos��      ����
    //scale��    �Ŵ���
    //layer��    ���ò���
    auto sp_create = [&](const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0) {
        Sprite* newsp = Sprite::create();
        newsp->initWithSpriteFrameName(pctname);
        newsp->setPosition(pos);
        newsp->setScale(scale);
        this->addChild(newsp, layer);
        return newsp;
        };

    /* ������ť�ıհ����� */
    //lambda���ʽ
    //normal��   ����״̬��ʾ
    //pressed��  ���״̬��ʾ
    //pos��      ����
    //scale��    �Ŵ���
    //layer��    ���ò���
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

    /************     ����     ************/

    constexpr int btnY1 = 180;              //��ť�߶�
    constexpr int btnY2 = 440;              //С��ť�߶�
    constexpr float btn_scale = 1.5f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;       //��ͼ�Ŵ���
    constexpr float word_scale = 2.0f;      //���ַŴ���
    const Vec2 bg(visibleSize / 2);         //����λ��
    const Vec2 ctn(1010, 760);

    /**************************************/

    /*********** �������� **********/
    /* �������ڱ��� */
    auto menu_bg = sp_create("options_bg.png", bg, map_scale, -1);


    /*********** ������ť **********/
    /* ���� ������Ϸ ��ť */
    auto resume = btn_create(
        "Levels/btn/continue_normal.png",
        "Levels/btn/continue_pressed.png",
        ctn, btn_scale, 1);
    resume->setTag(100);
    resume->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        //auto dimlayer = (LayerColor*)(main_scene->getChildByName("dimmer"));
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                main_scene->removeChildByName("dimmer");
                main_scene->removeChild(this);
                ((Button*)(main_scene->getChildByName("Menu")))->setEnabled(true);
                main_scene->getEventDispatcher()->setEnabled(true);
                break;
            default:
                break;
        }
        });

    /* ���� ���¿�ʼ ��ť */
    
    
    /* ���� ѡ��ؿ� ��ť */



    return true;
}