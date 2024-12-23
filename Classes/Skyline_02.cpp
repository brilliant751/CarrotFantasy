#pragma execution_character_set("utf-8")
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_02.h"
#include "GameMenu.h"
#include "MapChoose.h"
#include "Carrot.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "Monsters.h"
#include "Towers.h"
#include "tools.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;
using namespace ui;
using namespace std;
using namespace experimental;

#define MAX_WAVE 15     //��󲨴�

// ��ͼ����
extern int LEVEL;
extern each_map all_map[3];
extern bool is_open[3];
extern string stars_url[3];
// ��Ϸ
extern bool is_stop;   //�����Ϸ�Ƿ���ͣ���˵��ã�
extern bool is_paused;  //�����Ϸ�Ƿ���ͣ
extern int speed;      //��Ϸ����
extern clock_t timer;  //��ʱ��
extern int waves;      //��Ϸ����
extern int money;		//��Ǯ
extern Monster* cur_mons[20];   //��ǰ���й���
extern int lives;      //ջ��ָ�룬��ǰ���Ϲ�������
extern Target* target; //��������

/********** ������λ�� **********/
// ��ͼ��СΪ 12 * 8 ������
constexpr int mapX[13] = { 0, 95, 190, 285, 380, 475, 570, 665, 760, 855, 950, 1045, 1140 };
constexpr int mapY[9] = { 0, 95, 190, 285, 380, 475, 570, 665, 760 };

// ��������·��
static const Vec2 path[] = {
        Vec2(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + (mapY[5] + mapY[6]) / 2.0f),
        Vec2(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f),
        Vec2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f),
        Vec2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[5] + mapY[6]) / 2.0f),
};
static constexpr int top = 8; //ջ��λ��


/* ���²��� */
void Map_1_02::update_waves()
{
    ++waves;    //������һ��
    lives = 0;
    update_tag(mons_tag, waves);    //���µ�ǰ�����ǩ
    update_tag(least, waves);       //������ʼ�����ǩ
    auto left = getChildByName<Label*>("wavesleft");
    auto right = getChildByName<Label*>("wavesright");
    int yu = waves % 10;
    right->setString(to_string(yu));
    if (yu == 0)
        left->setString(to_string(waves / 10));
}

/* ���ɹ��� */
void Map_1_02::create_monster(float dt)
{
    if (get_tag_waves(mons_tag) != waves)
    {
        update_tag(mons_tag, waves);
    }
    if (mons_tag % 100 > MONS_NUM)  //������ȫ��ˢ��
    {
        int temp = least;
        for (int i = 0; i < MONS_NUM; ++i)
            if (this->getChildByTag(temp++))
                return;     //������ϴ��ڹ����򷵻�
        // ����ѵ���󲨴������ˢ��
        if (waves >= MAX_WAVE)
        {
            auto win_layer = Popwin::create_Layer();    //�����ɹ�����
            /* ���������� */
            auto dimlayer = LayerColor::create(Color4B(0, 0, 0, 128), 1620, 960);
            dimlayer->setName("dimmer");
            auto scene = Director::getInstance()->getRunningScene();
            scene->addChild(win_layer, 20);
            scene->addChild(dimlayer, 9);
            /* ��ͣ�������Ļ */
            // �˴���ѭ����ͣ����child���ļ����¼�
            scene->getEventDispatcher()->pauseEventListenersForTarget(scene, true);
            // ��ͣ����ˢ�ºͶ���
            scene->pauseSchedulerAndActions();
            /* �ָ�������ļ����¼� */
            win_layer->getEventDispatcher()->resumeEventListenersForTarget(win_layer, true);

            return;
        }
        // �������������һ��
        update_waves();
        return;
    }
    auto mon1 = Monster::create_Monster(PUPIL_1, path, top);
    mon1->setSpriteFrame(mons_url[waves]);
    mon1->setTag(mons_tag++);
    addChild(mon1, 2);
    //mons_tag++;
    cur_mons[lives++] = mon1;
    timer = clock();    //��¼���һ��ˢ��ʱ��
}

/* �����������ťˢ�� */
void Map_1_02::update_create(float dt) {
    auto sp1 = this->getChildByName<Sprite*>("create_bottle");
    auto sp2 = this->getChildByName<Sprite*>("create_shit");
    auto sp3 = this->getChildByName<Sprite*>("create_fan");
    if (money >= 100)
        sp1->setSpriteFrame("bottle_yes_create.png");
    else
        sp1->setSpriteFrame("bottle_no_create.png");
    if (money >= 120)
        sp2->setSpriteFrame("shit_yes_create.png");
    else
        sp2->setSpriteFrame("shit_no_create.png");
    if(money>=160)
        sp3->setSpriteFrame("fan_yes_create.png");
    else
        sp3->setSpriteFrame("fan_no_create.png");

}

/* �������ˢ�� */
void Map_1_02::update_money(float dt) {
    auto label = this->getChildByName<Label*>("lb_money");
    string num = to_string(money);
    label->setString(num);
}

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

    /* ��ʼ��ȫ�ֱ��� */
    is_stop = false;
    is_paused = false;
    waves = 1;      //����Ϊ1
    speed = 1;      //����Ϊ1
    LEVEL = 1;      //�ؿ����1
    lives = 0;      //��������0


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
    /* ��������bottle���� */
    auto create_bottle = sp_create("bottle_no_create.png", bg, map_scale, -10);
    create_bottle->setName("create_bottle");

    /* ��������shit���� */
    auto create_shit = sp_create("shit_no_create.png", bg, map_scale, -10);
    create_shit->setName("create_shit");

    /* ��������fan���� */
    auto create_fan = sp_create("fan_no_create.png", bg, map_scale, -10);
    create_fan->setName("create_fan");

    /* ���� ������Χ ���� */
    auto atk_range = sp_create("range.png", bg, 2, -10);//����һ����1.5������
    atk_range->setName("atk_range");

    /* ���� ���� ���� */
    auto up_level = sp_create("no_up.png", bg, map_scale, -10);
    up_level->setName("up_level");

    /* ���� ���� ���� */
    auto sell = sp_create("sell.png", bg, map_scale, -10);
    sell->setName("sell");

    // ˢ�½����������ť
    this->schedule(schedule_selector(Map_1_02::update_create), 0.1f);
    // ˢ�½������
    this->schedule(schedule_selector(Map_1_02::update_money), 0.1f);


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

    /* ����������� */
    auto lb_up_money = lb_create(this, 100, "fonts/HPSimplified_Bd.ttf", 25, bg, -10, 2);
    lb_up_money->setName("lb_up_money");

    /* �������۽�� */
    auto lb_sell_money = lb_create(this, 200, "fonts/HPSimplified_Bd.ttf", 25, bg, -10, 2);
    lb_sell_money->setName("lb_sell_money");

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
                if (is_paused == 0) {
                    btn->loadTextures("Levels/btn/game_continue_normal.png",
                        "Levels/btn/game_continue_pressed.png",
                        "Levels/btn/game_continue_normal.png");
                    is_paused = 1;
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
                    is_paused = 0;
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
    /* �л����� */
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

    /* �����ͼ */
    auto map_click_listener = EventListenerTouchOneByOne::create();
    map_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        if (pos.y >= 765 || pos.y <= 100 || pos.x >= 1380 || pos.x <= 240)
            return false;   //�����ͼ��λ����Ч
        // ֮ǰδ���
        if (map_clicked_2 == 0)
        {   // ֮ǰδ���
            cur_line = get_line(pos.y);            //��ȡ��ǰ��
            cur_row = get_row(pos.x);              //��ȡ��ǰ��
            cur_pos = get_po(cur_line, cur_row);   //��ȡ������������
            tag2_1 = cur_line * 12 + cur_row;      //����tag
            tag2_2 = 96 + tag2_1;                  //ʵ��tag
        }
        return true;
        };
    map_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    map_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        // ץȡ��������
        auto create1 = this->getChildByName<Sprite*>("create_bottle");
        auto create2 = this->getChildByName<Sprite*>("create_shit");
        auto create3 = this->getChildByName<Sprite*>("create_fan");
        // ץȡ���Ӿ���
        auto grid1 = this->getChildByTag<Sprite*>(tag2_1);
        auto grid2 = this->getChildByTag<Sprite*>(tag2_2);
        // ��ȡ��ǰ���״̬
        int state = occupy_2[cur_line][cur_row];
        // ��������λ�ã���ֹ������ͼ
        int up_po = cur_line < 4 ? -1 : 1;
            int right = 0;
            if (cur_row == 0)
                right = 2;
            else if (cur_row == 1)
                right = 1;
            else if (cur_row == 11)
                right = -2;
            else if (cur_row == 10)
                right = -1;
        
        // �趨λ��
        Vec2 po = get_po(cur_line, cur_row);
        Vec2 po1(po.x + (right - 2) * 55, po.y + 95 * up_po);
        Vec2 po2(po.x + right * 55, po.y + 95 * up_po);
        Vec2 po3(po.x + (right + 2) * 55, po.y + 95 * up_po);
        // ץȡһЩ����
        auto range = this->getChildByName<Sprite*>("atk_range");          //������Χ����
        auto up = this->getChildByName<Sprite*>("up_level");              //��������
        auto _sell = this->getChildByName<Sprite*>("sell");               //���۾���
        // ץȡһЩ��ǩ
        auto up_money = this->getChildByName<Label*>("lb_up_money");      //������Ҫ��Ǯ
        auto sell_money = this->getChildByName<Label*>("lb_sell_money");  //���ۿɵõ�Ǯ

        /* ������״̬��Ӧ��ͬ���� */
        if (map_clicked_2 == 1) //֮ǰ�Ѿ������һ���ɽ���������λ��
        {
            if (create1->getBoundingBox().containsPoint(pos)) {//�������bottle
                if (money >= 100) {
                    auto tower = Tower::create_Tower(0, cur_line, cur_row, this);
                    /* 2 0x yy */
                    //2��ͷ��ʾ������ 0������ xΪcur_line yyΪcur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);
                    // ���¸���״̬
                    occupy_2[cur_line][cur_row] = 3;
                    //�Ѳ���ʾ�ľ����������
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    create3->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    //���¸���״̬
                    map_clicked_2 = 0;
                    //����Ǯ
                    money -= 100;
                    auto audio = AudioEngine::play2d("sound/build_tower.mp3", false);
                }
            }
            else if (create2->getBoundingBox().containsPoint(pos)) {//�������shit
                if (money >= 120) {
                    auto tower = Tower::create_Tower(1, cur_line, cur_row, this);
                    /* 2 0x yy */
                    //2��ͷ��ʾ������ 0������ xΪcur_line yyΪcur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);
                    // ���¸���״̬
                    occupy_2[cur_line][cur_row] = 3;
                    //�Ѳ���ʾ�ľ����������
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    create3->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    //���¸���״̬
                    map_clicked_2 = 0;
                    //����Ǯ
                    money -= 120;
                    auto audio = AudioEngine::play2d("sound/build_tower.mp3", false);
                }

            }
            else if (create3->getBoundingBox().containsPoint(pos)) {//�������fan
                if (money >= 160) {//��һ�µ����
                    auto tower = Tower::create_Tower(2, cur_line, cur_row, this);
                    tower->schedule(schedule_selector(Tower::shoot_3), 2.0f);
                    /* 2 0x yy */
                    //2��ͷ��ʾ������ 0������ xΪcur_line yyΪcur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);
                    occupy_2[cur_line][cur_row] = 3;
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    create3->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    map_clicked_2 = 0;
                    money -= 120;
                    auto audio = AudioEngine::play2d("sound/build_tower.mp3", false);

            }
            }
            else {//�������κ�λ�� ��ȡ��ѡ��    
                //�Ѳ���ʾ�ľ����������
                create1->setZOrder(-10);
                create2->setZOrder(-10);
                create3->setZOrder(-10);
                grid1->setZOrder(-10);
                grid2->setZOrder(-10);
                //���¸���״̬
                map_clicked_2 = 0;
            }
        }
        else if (map_clicked_2 == 2)//֮ǰ�Ѿ������һ��������
        {   // ��������ť�ɰ� ���� or sell
            auto tower = this->getChildByTag<Tower*>(2 * 10000 + cur_line * 100 + cur_row);    //��ȡ������       
            int tower_level = tower->get_level();  //��ȡ�������ȼ�
            int um = tower->get_up_money();     //���������Ǯ
            int sm = tower->get_sell_money();   //����������Ǯ

            if (up->getBoundingBox().containsPoint(pos)) {//����������
                if (money >= um && tower_level < 2) {//��������
                    tower->up_level();          //���� todo���ɼӶ���
                    money -= um;                //����Ǯ
                    auto audio = AudioEngine::play2d("sound/uplevel_tower.mp3", false);
                }
            }
            else if (_sell->getBoundingBox().containsPoint(pos)) {//�����۾���
                tower->remove();    //���
                money += sm;        //���������Ǯ
                occupy_2[cur_line][cur_row] = 0;    //���¸���״̬
                auto audio = AudioEngine::play2d("sound/sell_tower.mp3", false);
            }
            //�Ѳ���ʾ�ľ����������
            /* ZOrder */
            range->setZOrder(-10);
            up->setZOrder(-10);
            _sell->setZOrder(-10);
            up_money->setZOrder(-10);
            sell_money->setZOrder(-10);
            //Ϊ��ֹrange������Χ ���ڿ��м��λ��
            range->setPosition(Vec2(500, 500));
            //���¸���״̬
            map_clicked_2 = 0;
        }
        else {//֮ǰ��δ���һ�����Խ���������λ��
            if (state == 1) {//���ڵ����һ�����ɵ����λ��
                auto ban = this->getChildByTag<Sprite*>(192 + cur_line * 12 + cur_row);//��ȡban����
                ban->setOpacity(255);                    //�ָ�͸����Ϊ100%
                auto fadeout = FadeOut::create(1.0f);    //�𽥵�ȥ
                ban->runAction(fadeout);                 //ִ�ж���
            }
            else if (state == 0) {//���ڵ����һ�����Խ���������λ��
                grid1 = this->getChildByTag<Sprite*>(tag2_1);//��ȡ���߿�
                grid2 = this->getChildByTag<Sprite*>(tag2_2);//��ȡʵ�߿�
                //���¾���λ�ü�ZOrder
                create1->setPosition(po1);
                create2->setPosition(po2);
                create3->setPosition(po3);
                create1->setZOrder(4);
                create2->setZOrder(4);
                create3->setZOrder(4);
                grid1->setZOrder(4);
                grid2->setZOrder(4);
                //���¸���״̬
                map_clicked_2 = 1;
            }
            else if (state == 3) {//���ڵ����һ��������
                auto tower = this->getChildByTag<Tower*>(2 * 10000 + cur_line * 100 + cur_row);  //��ȡ������              
                int tower_level = tower->get_level();
                float range_scale = tower->get_scale();
                /* ����������� ��ǩλ�� */
                Vec2 up_pos;
                Vec2 sell_pos;
                Vec2 up_money_pos;
                Vec2 sell_money_pos;
                if (cur_line > 1 && cur_line < 7) {//���������м� �������� �������� 
                    up_pos = Vec2(cur_pos.x, cur_pos.y + 95);
                    sell_pos = Vec2(cur_pos.x, cur_pos.y - 95);
                }
                else {
                    if (cur_line == 1) {//��������������
                        int right = cur_row == 11 ? -1 : 1;
                        sell_pos = Vec2(cur_pos.x, cur_pos.y - 95);//��������
                        up_pos = Vec2(cur_pos.x + 95 * right, cur_pos.y);//��������11������ ��������
                    }
                    else {//cur_line==7 ��������������
                        int left = cur_row == 0 ? 1 : -1;
                        sell_pos = Vec2(cur_pos.x + 95 * left, cur_pos.y);//���ۣ���0������ ��������
                        up_pos = Vec2(cur_pos.x, cur_pos.y + 95);//��������
                    }
                }
                //���ݾ�������ǩλ��
                up_money_pos = Vec2(up_pos.x + 12, up_pos.y - 30);
                sell_money_pos = Vec2(sell_pos.x + 12, sell_pos.y - 30);

                /* ���ù�����Χ��С */
                range->setScale(range_scale);

                /* ����λ�� */
                range->setPosition(cur_pos);
                up->setPosition(up_pos);
                _sell->setPosition(sell_pos);
                up_money->setPosition(up_money_pos);
                sell_money->setPosition(sell_money_pos);

                /* ��Ⱦ */
                /* up+up_money */
                if (tower_level == 2)
                    up->setSpriteFrame("top_level.png");
                else {
                    int um = tower->get_up_money();
                    string text = to_string(um);
                    //����money������money�Ĺ�ϵ��Ⱦ
                    if (money >= um)
                        up->setSpriteFrame("yes_up.png");
                    else
                        up->setSpriteFrame("no_up.png");
                    up_money->setString(text);
                }
                /* sell_money */
                int sm = tower->get_sell_money();
                string text = to_string(sm);
                sell_money->setString(text);

                /* ZOrder */
                range->setZOrder(1);
                up->setZOrder(3);
                _sell->setZOrder(3);
                if (tower_level < 2)
                    up_money->setZOrder(4);
                sell_money->setZOrder(4);
                //���¸���״̬
                map_clicked_2 = 2;
            }
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(map_click_listener, this);


    /*********** �������� **********/
    this->schedule(schedule_selector(Map_1_02::create_monster), 1.0f / speed);









    /* ��������ʱ */
    auto count = CountDown::create_Layer();
    this->addChild(count, 10);



    return true;
}