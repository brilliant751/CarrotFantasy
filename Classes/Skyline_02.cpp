#pragma execution_character_set("utf-8")
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_02.h"
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
Scene* Map_1_02::create_Scene()
{
    return Map_1_02::create();
}

/* ��ʼ������ */
bool Map_1_02::init()
{
    if (!Scene::init())
        return false;

    const Vec2 origin = Vec2(240, 100); //��ͼ�������
    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/1-02/1_02.plist");
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

    /* �����ı��ıհ����� */
    //lambda���ʽ
    //int num/string text��     �ı�����/�ı�����
    //ttf��      �����ļ���
    //size��     �����С
    //pos��      ����
    //layer��    ���ò���
    //color:     ��ɫ���ࣺ
    //                    0 - ��ɫ
    //                    1 - ����
    auto lb_create1 = [&](const int num, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0) {
        string text = to_string(num);
        auto myLabel = Label::createWithTTF(text, ttf, size);
        myLabel->setPosition(pos);
        myLabel->enableBold();
        if (color == 1)
            myLabel->setColor(Color3B(255, 246, 143));
        this->addChild(myLabel, layer);
        return myLabel;
        };

    auto lb_create2 = [&](const string text, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0) {
        auto myLabel = Label::createWithTTF(text, ttf, size);
        myLabel->setPosition(pos);
        myLabel->enableBold();
        if (color == 1)
            myLabel->setColor(Color3B(255, 246, 143));
        this->addChild(myLabel, layer);
        return myLabel;
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
    const Vec2 po_bg_waves(740, topY + 10);  //waves��λ��
    const Vec2 po_waves_left(715, topY + 10);  //waves_leftλ��
    const Vec2 po_waves_right(765, topY + 10);  //waves_rightλ��
    const Vec2 po_chp_bg(origin.x + mapX[8]+30, origin.y + mapY[2]-10);   //�ܲ�Ѫ����ͼλ��
    const Vec2 po_chp_num(origin.x + mapX[8]+45, origin.y + mapY[2]-10);  //�ܲ�Ѫ������λ��
    const Vec2 po_lb_total_waves(880, topY + 10);           //������λ��
    const Vec2 crt(origin.x+mapX[7]+(mapX[1])/2.0f, origin.y + mapY[2]);             //�ܲ�λ��
    const Vec2 born(origin.x + mapX[9]/2.0f, origin.y + (mapY[5]+mapY[6])/2.0f); //���������
    /* �ϰ���λ�� */
    const Vec2 planet_1(origin.x + (mapX[4] + mapX[3]) / 2.0f, origin.y + (mapY[4] + mapY[1]) / 2.0f);
    const Vec2 planet_2(origin.x + (mapX[8] + mapX[9]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 planet_3(origin.x + (mapX[11]+mapX[10])/2.0f , origin.y + (mapY[6] + mapY[5]) / 2.0f);
    const Vec2 planet_4(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 balloon(origin.x + mapX[11], origin.y + mapY[4]);
    const Vec2 trees(origin.x + mapX[5] / 2.0f, origin.y + (mapY[6] + mapY[5]) / 2.0f);
    const Vec2 cloud_1(origin.x + (mapX[7] + mapX[6]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 cloud_2(origin.x + (mapX[5] + mapX[6]) / 2.0f, origin.y + mapY[5] / 2.0f);
    const Vec2 rainbow(origin.x + (mapX[2]) / 2.0f, origin.y + (mapY[4] + mapY[1]) / 2.0f);

    /**************************************/

    /*********** �������� **********/
    /* �������� */
    auto map_bg_02 = sp_create("1_02_bg.png", bg, map_scale, -2);

    /* �����ܲ� */
    auto carrot_02 = sp_create("HP_MAX.PNG", crt, map_scale, 0);

    /* �����ܲ�Ѫ����ͼ */
    auto chp_bg = sp_create("Hp.png", po_chp_bg, map_scale, 0);

    /* ��������״̬�� */
    auto top_bg_02 = sp_create("top_bg02.png", topbg, map_scale, -1);

    /* ������ͣ����ʾ */
   // auto pausing_02 = sp_create("paused_02.png", topbg, word_scale, 0);

    /* ������������� */
    auto start_point_02 = sp_create("start_point02.png", born, map_scale, 0);

    /* �������ټ� */
    auto spd_shift_02 = sp_create("game_speed_1_02.png", spd, map_scale, 0);
    spd_shift_02->setName("spd_shift_02");

    /* �����ϰ��� */
    auto planet1 = sp_create("Barrier_One_1.png", planet_1, map_scale, 0);
    auto planet2 = sp_create("Barrier_One_1.png", planet_2, map_scale, 0);
    auto planet3 = sp_create("Barrier_One_1.png", planet_3, map_scale, 0);
    auto planet4 = sp_create("Barrier_One_1.png", planet_4, map_scale, 0);
    auto _balloon = sp_create("Barrier_Four_1.png", balloon, map_scale, 0);
    auto _trees = sp_create("Barrier_Four_2.png", trees, map_scale, 0);
    auto _cloud1 = sp_create("Barrier_One_2.png", cloud_1, map_scale, 0);
    auto _cloud2 = sp_create("Barrier_One_2.png", cloud_2, map_scale, 0);
    auto _rainbow = sp_create("Barrier_Two_1.png", rainbow, map_scale, 0);

    /* waves�� */
    auto bg_waves = sp_create("game)waves02.png", po_bg_waves, map_scale, 0);

    /*********** ������ǩ ***********/
    /* �����ܲ�Ѫ������ */
    auto chp_num = lb_create1(c_hp, "fonts/HPSimplified_Bd.ttf", 27, po_chp_num, 1);

    /* ����total_waves */
    auto lb_total_waves = lb_create2("/20������", "fonts/�����ֺ��μ���.ttf", 34, po_lb_total_waves, 2);

    /* ����wavesʮλ */
    auto waves_left = lb_create1(waves / 10, "fonts/�����ֺ��μ���.ttf", 34, po_waves_left, 2, 1);

    /* ����waves��λ */
    auto waves_right = lb_create1(waves % 10, "fonts/�����ֺ��μ���.ttf", 34, po_waves_right, 2, 1);




    /*********** ������ť **********/
     /* �����˵� */
    auto game_menu = btn_create(
        "Levels/btn/gamemenu_btn_normal.png",
        "Levels/btn/gamemenu_btn_pressed.png",
        gmmenu, btn_scale, 0);
    game_menu->setName("Menu");
    game_menu->addTouchEventListener([this, v_size = visibleSize](Ref* sender, Widget::TouchEventType type) {
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
    game_pause->setName("game_pause");
    game_pause->addTouchEventListener([this, v_size = visibleSize](Ref* sender, Widget::TouchEventType type) {
        auto btn = (Button*)(this->getChildByName("game_pause"));
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (is_pause == 0) {
                btn->loadTextures("Levels/btn/game_continue_normal.png",
                    "Levels/btn/game_continue_pressed.png",
                    "Levels/btn/game_continue_normal.png");
                is_pause = 1;
                //todo:��ͣ״̬
            }
            else {
                btn->loadTextures("Levels/btn/game_pause.png",
                    "Levels/btn/game_pause.png",
                    "Levels/btn/game_pause.png");
                is_pause = 0;
                //todo:��ʼ״̬
            }
            break;
        default:
            break;
        }
        });


    /* �����¼� */
    /* spd */
    auto spd_click_listener = EventListenerTouchOneByOne::create();
    spd_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("spd_shift_02"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    spd_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    spd_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto sp = (Sprite*)(this->getChildByName("spd_shift_02"));
        if (speed == 1) {
            sp->setSpriteFrame("game_speed_2_02.png");
            speed = 2;
        }
        else {
            sp->setSpriteFrame("game_speed_1_02.png");
            speed = 1;
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(spd_click_listener, this);















    /* ��������ʱ */
  /*  auto count = CountDown::create_Layer();
    this->addChild(count, 10);*/



    return true;
}