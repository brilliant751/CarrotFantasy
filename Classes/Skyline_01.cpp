
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

#define GR_LEN 95   //����߳�

/********** ������λ�� **********/
// ��ͼ��СΪ 12 * 8 ������
constexpr int mapX[13] = { 0, 95, 190, 285, 380, 475, 570, 665, 760, 855, 950, 1045, 1140 };
constexpr int mapY[9] = { 0, 95, 190, 285, 380, 475, 570, 665, 760 };
/********************************/

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

	const Vec2 origin = Vec2(240, 100); //��ͼ�������
	auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

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

    constexpr int topY = 814;               //�����߶�
    constexpr float btn_scale = 1.4f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;       //��ͼ�Ŵ���
    constexpr float word_scale = 2.0f;      //���ַŴ���
    const Vec2 bg(visibleSize / 2);         //��ͼλ��
    const Vec2 topbg(810, topY);            //����λ��
    const Vec2 gmmenu(1270, topY);          //�˵�λ��
    const Vec2 gmpause(1180, topY);         //��ͣλ��
    const Vec2 spd(1070, topY);             //����λ��

    const Vec2 crt(1250, origin.y + mapY[6]);             //�ܲ�λ��
    const Vec2 born(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + mapY[6]); //���������
    /* �ϰ���λ�� */
    const Vec2 brr1_1(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 brr1_2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 brr1_3(origin.x + (mapX[2] + mapX[3]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f);
    const Vec2 brr1_4(origin.x + (mapX[9] + mapX[10]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f);
    const Vec2 brr2_1(origin.x + mapX[6], origin.y + (mapY[2] + mapY[3]) / 2.0f);
    const Vec2 brr4_1(origin.x + mapX[6], origin.y + mapY[6]);
    const Vec2 brr4_2(origin.x + mapX[4], origin.y + mapY[6]);
    const Vec2 brr4_3(origin.x + mapX[8], origin.y + mapY[6]);

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

    /* ������������� */
    auto start_point = sp_create("start_point.png", born, map_scale, 0);

    /* �������ټ� */
    auto spd_shift = sp_create("game_speed_1.png", spd, map_scale, 0);

    /* �����ϰ��� */
    auto _1brr1 = sp_create("Barrier_One_1.png", brr1_1, map_scale, 0);
    auto _1brr2 = sp_create("Barrier_One_1.png", brr1_2, map_scale, 0);
    auto _1brr3 = sp_create("Barrier_One_2.png", brr1_3, map_scale, 0);
    auto _1brr4 = sp_create("Barrier_One_2.png", brr1_4, map_scale, 0);
    auto _2brr1 = sp_create("Barrier_Two_1.png", brr2_1, map_scale, 0);
    auto _4brr1 = sp_create("Barrier_Four_1.png", brr4_1, map_scale, 0);
    auto _4brr2 = sp_create("Barrier_Four_3.png", brr4_2, map_scale, 0);
    auto _4brr3 = sp_create("Barrier_Four_3.png", brr4_3, map_scale, 0);



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
    game_pause->setName("pause");


	return true;
}