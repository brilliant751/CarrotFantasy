
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_01.h"
#include "GameMenu.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* �������� */
Scene* Map_1_01::create_Scene()
{
	return Map_1_01::create();
}



/* ��ʼ������ */
bool Map_1_01::init()
{
	if (!Scene::init())
		return false;

	const Vec2 origin = Vec2(305, 120); //��ͼ�������
	auto visibleSize = Director::getInstance()->getVisibleSize();   //(2050��1200)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/1-01/1-01.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Barriers/Barriers.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Carrot/Carrot.plist");

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
    constexpr int locks = 220;              //���߶�
    constexpr float btn_scale = 1.4f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;       //��ͼ�Ŵ���
    constexpr float word_scale = 2.0f;      //���ַŴ���
    const Vec2 bg(visibleSize / 2);         //��ͼλ��
    const Vec2 crt(1000, 1000);             //�ܲ�λ��
    const Vec2 topbg(1024, 1022);           //����λ��
    const Vec2 gmmenu(1630, 1022);          //�˵�λ��
    const Vec2 gmpause(1520, 1022);       //��ͣλ��

    /**************************************/

    /*********** �������� **********/
    /* �������� */
    auto map_bg = sp_create("1-01_bg.png", bg, map_scale, -2);

    /* �����ܲ� */
    auto carrot = sp_create("HP_MAX.PNG", crt, map_scale, 0);

    /* ��������״̬�� */
    auto top_bg = sp_create("top_bg.png", topbg, map_scale, -1);

    /* ������ͣ����ʾ */
    auto pausing = sp_create("paused.png", topbg, word_scale, 0);


    /*********** ������ť **********/
    /* �����˵� */
    auto game_menu = btn_create(
        "Levels/btn/gamemenu_btn_normal.png",
        "Levels/btn/gamemenu_btn_pressed.png",
        gmmenu, btn_scale, 0);
    game_menu->setName("Menu");
    game_menu->addTouchEventListener([this, v_size=visibleSize](Ref* sender, Widget::TouchEventType type) {
        auto menu_layer = PauseMenu::create_Layer();    //���������˵�
        auto menu = (Button*)(this->getChildByName("Menu"));
        /* ���������� */
        auto dimlayer = LayerColor::create(Color4B(0, 0, 0, 128), v_size.width, v_size.height);
        dimlayer->setName("dimmer");
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->addChild(menu_layer, 10);
                this->addChild(dimlayer, 9);
                /* ��ͣ�������ļ����¼� */
                //�˴���ѭ����ͣ����child���ļ����¼�
                this->getEventDispatcher()->pauseEventListenersForTarget(this, true);
                /* �ָ�������ļ����¼� */
                this->getEventDispatcher()->resumeEventListenersForTarget(menu_layer, true);
                break;
            default:
                break;
        }
        });
    /* ������ͣ�� */
    auto game_pause = btn_create(
        "Levels/btn/game_pause.png",
        "Levels/btn/game_pause.png",
        gmpause, btn_scale, 0);

	return true;
}