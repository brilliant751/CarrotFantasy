#pragma execution_character_set("utf-8")
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_02.h"
#include "GameMenu.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "tools.h"

USING_NS_CC;
using namespace ui;
using namespace std;

#define GR_LEN 95   //����߳�
static int top = 0;    // ջ��ָ��

int map_clicked_2 = 0;//״̬
int tag2_1;
int tag2_2;

/********** ������λ�� **********/
// ��ͼ��СΪ 12 * 8 ������
constexpr int mapX[13] = { 0, 95, 190, 285, 380, 475, 570, 665, 760, 855, 950, 1045, 1140 };
constexpr int mapY[9] = { 0, 95, 190, 285, 380, 475, 570, 665, 760 };

int occupy_2[8][12] = {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    0,2,2,0,0,0,0,0,0,0,0,0,
    0,2,2,0,1,1,1,1,1,1,2,0,
    0,0,0,0,2,0,2,0,2,1,2,2,
    0,0,1,1,1,1,1,1,1,1,2,2,
    2,2,1,2,0,2,0,0,2,2,0,0,
    0,0,1,1,1,1,1,1,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,1,1
};
//��ʾ�����Ƿ�ռ��
//-1������Ч����0����δռ�ã�1���������ߵ�·����2���������ϰ���

//const Vec2 origin = Vec2(240, 100); //��ͼ�������
//
////��ȡline row������λ��
//Vec2 get_po(int line, int row) {
//    float x = origin.x + (0.5 + row) * 95;
//    float y = origin.y + (7.5 - line) * 95;
//    return Vec2(x, y);
//}
//
//int get_line(float y) {
//    return round(7.5 - (y - origin.y) / 95);
//}
//
//int get_row(float x) {
//    return round((x - origin.x) / 95 - 0.5);
//}

//create 
void Map_1_02::update_create(float dt) {
    auto sp1 = this->getChildByName<Sprite*>("create_bottom");
    auto sp2 = this->getChildByName<Sprite*>("create_shit");
    auto sp3 = this->getChildByName<Sprite*>("create_fan");
    if (money >= 100)
        sp1->setSpriteFrame("bottom_yes_create.png");
    else
        sp1->setSpriteFrame("bottom_no_create.png");
    if (money >= 120)
        sp2->setSpriteFrame("shit_yes_create.png");
    else
        sp2->setSpriteFrame("shit_no_create.png");
    if(money>=160)
        sp3->setSpriteFrame("fan_yes_create.png");
    else
        sp3->setSpriteFrame("fan_no_create.png");

}

////������λ��תΪ����ֵ
//int judgePosition(const Vec2& pos)
//{
//    int x, y;
//    x = (pos.x- origin.x) / 95+1;
//    y = (pos.y - origin.y) / 95+1;
//    return occupy[x][y];
//}
////������λ��תΪ��������ֵ
//Vec2 rePosition(const Vec2& pos)
//{
//    int x, y;
//    x = (pos.x - origin.x) / 95;
//    y = (pos.y - origin.y) / 95;
//    return Vec2(origin.x+mapX[x]+mapX[1] / 2.0f, origin.y+ mapY[y] + mapY[1] / 2.0f);
//}

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

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/1-02/1_02.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Barriers/Barriers.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Carrot/Carrot.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/tower_click/tower_click.plist");


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
    const Vec2 po_lb_money(390, topY + 10);           //���λ��
    const Vec2 crt(origin.x+mapX[7]+(mapX[1])/2.0f, origin.y + mapY[2]);             //�ܲ�λ��
    const Vec2 born(origin.x + mapX[9]/2.0f, origin.y + (mapY[5]+mapY[6])/2.0f); //���������
    /* �ϰ���λ�� */
    const Vec2 planet_1(origin.x + (mapX[4] + mapX[3]) / 2.0f, origin.y + (mapY[4] + mapY[1]) / 2.0f);
    const Vec2 planet_2(origin.x + (mapX[8] + mapX[9]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 planet_3(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[6] + mapY[5]) / 2.0f);
    const Vec2 planet_4(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 balloon(origin.x + mapX[11], origin.y + mapY[4]);
    const Vec2 trees(origin.x + mapX[2], origin.y + mapY[6]);
    const Vec2 cloud_1(origin.x + (mapX[7] + mapX[6]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 cloud_2(origin.x + (mapX[5] + mapX[6]) / 2.0f, origin.y + mapY[5] / 2.0f);
    const Vec2 rainbow_1(origin.x + mapX[1], origin.y + (mapY[4] + mapY[1]) / 2.0f);
    const Vec2 rainbow_2(origin.x + mapX[9], origin.y + (mapY[4] + mapY[1]) / 2.0f);

    /**************************************/

    /*********** �������� **********/
    /* �������� */
    auto map_bg = sp_create("1_02_bg.png", bg, map_scale, -2);

    /* �����ܲ� */
    auto carrot = sp_create("HP_MAX.PNG", crt, map_scale, 0);

    /* �����ܲ�Ѫ����ͼ */
    auto chp_bg = sp_create("Hp.png", po_chp_bg, map_scale, 0);

    /* ��������״̬�� */
    auto top_bg = sp_create("top_bg.png", topbg, map_scale, -1);

    /* ������ͣ����ʾ */
    auto pausing = sp_create("paused.png", topbg, word_scale, -2);
    pausing->setName("pausing");

    /* ������������� */
    auto start_point_02 = sp_create("start_point02.png", born, map_scale, 0);

    /* �������ټ� */
    auto spd_shift = sp_create("game_speed_1.png", spd, map_scale, 0);
    spd_shift->setName("spd_shift");

    /* waves�� */
    auto bg_waves = sp_create("game)waves.png", po_bg_waves, map_scale, 0);
    bg_waves->setName("bgwaves");

    /* �����ϰ��� */
    auto planet1 = sp_create("Barrier_One_1.png", planet_1, map_scale, 0);
    auto planet2 = sp_create("Barrier_One_1.png", planet_2, map_scale, 0);
    auto planet3 = sp_create("Barrier_One_1.png", planet_3, map_scale, 0);
    auto planet4 = sp_create("Barrier_One_1.png", planet_4, map_scale, 0);
    auto _balloon = sp_create("Barrier_Four_1.png", balloon, map_scale, 0);
    auto _trees = sp_create("Barrier_Four_2.png", trees, map_scale, 0);
    auto _cloud1 = sp_create("Barrier_One_2.png", cloud_1, map_scale, 0);
    auto _cloud2 = sp_create("Barrier_One_2.png", cloud_2, map_scale, 0);
    auto _rainbow1 = sp_create("Barrier_Two_1.png", rainbow_1, map_scale, 0);
    auto _rainbow2 = sp_create("Barrier_Two_1.png", rainbow_2, map_scale, 0);


    /* ����������� + ���ɵ������ */
    for (int i = 1; i < 8; i++)
        for (int j = 0; j < 12; j++) {
            Vec2 po = get_po(i, j);
            if (occupy_2[i][j] == 0) {
                auto sp1 = sp_create("start_sprite02.png", po, map_scale, -10);
                sp1->setTag(i * 12 + j);
                auto sp2 = sp_create("grid_02.png", po, map_scale, -10);
                sp2->setTag(96 + i * 12 + j);
            }
            else if (occupy_2[i][j] == 1) {
                auto sp = sp_create("cant_build02.png", po, map_scale, 2);
                sp->setTag(192 + i * 12 + j);
                sp->setOpacity(0);
            }
        }
    /* ��������bottom���� */
    auto create_bottom = sp_create("bottom_no_create.png", bg, map_scale, -10);
    create_bottom->setName("create_bottom");

    /* ��������shit���� */
    auto create_shit = sp_create("shit_no_create.png", bg, map_scale, -10);
    create_shit->setName("create_shit");

    /* ��������fan���� */
    auto create_fan = sp_create("fan_no_create.png", bg, map_scale, -10);
    create_fan->setName("create_fan");

    this->schedule(schedule_selector(Map_1_02::update_create), 0.1f);

    ///* ��������λ�� */
    //auto grid_02 = sp_create("grid_02.png",bg, map_scale, -2);
    //grid_02->setName("grid");


    /*********** ������ǩ ***********/
    /* �����ܲ�Ѫ������ */
    auto chp_num = lb_create1(c_hp, "fonts/HPSimplified_Bd.ttf", 27, po_chp_num, 1);

    /* ����total_waves */
    auto lb_total_waves = lb_create2("/20������", "fonts/�����ֺ��μ���.ttf", 34, po_lb_total_waves, 2);
    lb_total_waves->setName("totalwaves");


    /* ����wavesʮλ */
    auto waves_left = lb_create1(waves / 10, "fonts/�����ֺ��μ���.ttf", 34, po_waves_left, 2, 1);
    waves_left->setName("wavesleft");

    /* ����waves��λ */
    auto waves_right = lb_create1(waves % 10, "fonts/�����ֺ��μ���.ttf", 34, po_waves_right, 2, 1);
    waves_right->setName("wavesright");

    /* ����������� */
    auto lb_money = lb_create1(money, "fonts/HPSimplified_Bd.ttf", 35, po_lb_money, 1);
    lb_money->setName("lb_money");

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
        auto btn = this->getChildByName<Button*>("game_pause");
        //auto mons = this->getChildByTag<Monster*>(0);
        auto pausing = this->getChildByName<Sprite*>("pausing");
        auto bg_waves = this->getChildByName<Sprite*>("bgwaves");
        auto total_waves = this->getChildByName<Sprite*>("totalwaves");
        auto waves_left = this->getChildByName<Sprite*>("wavesleft");
        auto waves_right = this->getChildByName<Sprite*>("wavesright");
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                if (is_pause == 0) {
                    btn->loadTextures("Levels/btn/game_continue_normal.png",
                        "Levels/btn/game_continue_pressed.png",
                        "Levels/btn/game_continue_normal.png");
                    is_pause = 1;
                    //mons->unscheduleUpdate();   //����ֹͣ�ƶ�
                    /* ��ǩ�л� */
                    bg_waves->setZOrder(-3);
                    total_waves->setZOrder(-3);
                    waves_left->setZOrder(-3);
                    waves_right->setZOrder(-3);
                    pausing->setZOrder(3);
                    //todo:������ͣ״̬
                }
                else {
                    btn->loadTextures("Levels/btn/game_pause.png",
                        "Levels/btn/game_pause.png",
                        "Levels/btn/game_pause.png");
                    is_pause = 0;
                    //mons->scheduleUpdate();     //���￪ʼ�ƶ�
                    /* ��ǩ�л� */
                    bg_waves->setZOrder(2);
                    total_waves->setZOrder(2);
                    waves_left->setZOrder(2);
                    waves_right->setZOrder(2);
                    pausing->setZOrder(-3);
                    //todo:���뿪ʼ״̬
                }
                break;
            default:
                break;
        }
        });



    /*********** �����¼� **********/
    /* �������� */
    auto spd_click_listener = EventListenerTouchOneByOne::create();
    spd_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("spd_shift"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    spd_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    spd_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto sp = (Sprite*)(this->getChildByName("spd_shift"));
        if (speed == 1) {
            sp->setSpriteFrame("game_speed_2.png");
            speed = 2;
        }
        else {
            sp->setSpriteFrame("game_speed_1.png");
            speed = 1;
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(spd_click_listener, this);
  
    auto map_click_listener = EventListenerTouchOneByOne::create();
    map_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        if (pos.y >= 765)
            return false;
        return true;

        };
    map_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    map_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        int line = get_line(pos.y);
        int row = get_row(pos.x);
        auto create1 = this->getChildByName<Sprite*>("create_bottom");
        auto create2 = this->getChildByName<Sprite*>("create_shit");
        auto create3 = this->getChildByName<Sprite*>("create_fan");
        auto grid1 = this->getChildByTag<Sprite*>(tag2_1);//֮ǰ��
        auto grid2 = this->getChildByTag<Sprite*>(tag2_2);//֮ǰ��
        int state = occupy_2[line][row];
        int up = line < 4 ? -1 : 1;
        int right = 0;
        if (row == 0)
            right = 2;
        else if (row == 1)
            right = 1;
        else if (row == 11)
            right = -2;
        else if (row == 10)
            right = -1;
        Vec2 po = get_po(line, row);
        Vec2 po1(po.x + (right - 2) * 55, po.y + 95 * up);
        Vec2 po2(po.x + right * 55, po.y + 95 * up);
        Vec2 po3(po.x + (right + 2) * 55, po.y + 95 * up);

        if (map_clicked_2 == 1) {//�Ѿ������һ���ɽ���������λ��
            if (create1->getBoundingBox().containsPoint(pos)) {//�������bottom
                if (money >= 100) {
                    //todo:����bottom 
                }
            }
            else if (create2->getBoundingBox().containsPoint(pos)) {//�������shit
                if (money >= 120) {
                    //todo:����shit

                }
            }
            else if (create3->getBoundingBox().containsPoint(pos)) {//�������shit
                if (money >= 160) {
                    //todo:����fan

                }
            }

            else {//�������κ�λ��
                create1->setZOrder(-10);
                create2->setZOrder(-10);
                create3->setZOrder(-10);
                grid1->setZOrder(-10);
                grid2->setZOrder(-10);
            
                map_clicked_2 = 0;
            }
        }
        else {//��δ���һ�����Խ���������λ��
            if (state == 1) {//���ڵ����һ�����ɵ����λ��
                auto ban = this->getChildByTag<Sprite*>(192 + line * 12 + row);
                ban->setOpacity(255);
                auto fadeout = FadeOut::create(1.0f);
                ban->runAction(fadeout);
            }
            else if (state == 0) {//���ڵ����һ�����Խ���������λ��
                tag2_1 = line * 12 + row;
                tag2_2 = 96 + tag2_1;
                grid1 = this->getChildByTag<Sprite*>(tag2_1);
                grid2 = this->getChildByTag<Sprite*>(tag2_2);
                create1->setPosition(po1);
                create2->setPosition(po2);
                create3->setPosition(po3);
                create1->setZOrder(2);
                create2->setZOrder(2);
                create3->setZOrder(2);
                grid1->setZOrder(2);
                grid2->setZOrder(2);
                map_clicked_2 = 1;
            }
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(map_click_listener, this);













    /* ��������ʱ */
    auto count = CountDown::create_Layer();
    this->addChild(count, 10);



    return true;
}