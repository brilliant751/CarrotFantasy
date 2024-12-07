
#include "StartScene.h"
#include "EnterScene.h"
#include "MapChoose.h"
#include "HelpScene_1.h"
#include "HelpScene_2.h"
#include "HelpScene_3.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* ����ļ��޷��򿪣���ӡ������Ϣ */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* �������� */
Scene* HelpScene_2::create_Scene()
{
    return HelpScene_2::create();
}

/* ���ذ�ť�л���StartScene */
void HelpScene_2::back_onButtonClicked(Ref* sender) {
    auto next = StartScene::create_Scene();
    Director::getInstance()->popScene();
}

/* ������ʼ�� */
bool HelpScene_2::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
    //normal_name��   ����״̬��ͼ���е�����
    //pressed_name��  ѡ��״̬��ͼ���е�����
    //locked_name��   ���ɵ��״̬��ͼ���е����� 
    //pos��           ����
    //scale��         �Ŵ���
    //layer��         ���ò���
    //btn_type:       ��ť���
    //                         1 - home
    auto btn_create = [&](const string& normal_name, const string& pressed_name, const string& locked_name,
        const Vec2& pos, int btn_type, const float& scale = 1.1f, int layer = 0) {
            auto temp_btn = Button::create(normal_name, pressed_name, locked_name);
            temp_btn->setPosition(pos);
            temp_btn->setScale(scale);

            temp_btn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        switch (btn_type) {
                            case 1:
                                back_onButtonClicked(this);
                                break;
                            default:
                                break;
                        };
                        break;
                    default:
                        break;
                }
                });
            addChild(temp_btn, layer);

            return temp_btn;
        };

    /************     ����     ************/

    const Vec2 po_bg(visibleSize / 2);     //��ͼλ��    
    const Vec2 po_monsters(980, 500);      //monsters��ͼλ��
    constexpr float btn_scale = 1.1f;      //��ť�Ŵ���
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 po_btn_back(360, 920);      //home��ťλ��
    const Vec2 po_help(750, 922);          //column_helpλ�� 
    const Vec2 po_monster(980, 920);       //column monsterλ��  
    const Vec2 po_tower(1200, 925);        //column_towerλ�� 
    const Vec2 po_monster_1(550, 480);     //monster_1��Ļλ�� 
    const Vec2 po_monster_2(980, 480);     //monster_2��Ļλ��
    const Vec2 po_monster_3(1400, 480);    //monster_3��Ļλ�� 
    const Vec2 po_speed_1(757, 412);       //speed_1��Ļλ�� 
    const Vec2 po_blood_1(757, 350);       //blood_1��Ļλ�� 
    const Vec2 po_speed_2(1177, 412);      //speed_2��Ļλ�� 
    const Vec2 po_blood_2(1177, 350);      //blood_2��Ļλ�� 
    const Vec2 po_caption(980, 265);       //bottom��Ļλ�� 

    /**************************************/

    /********** �������� **********/
    /* �������� */
    auto bg = sp_create("help_bg.png", po_bg, map_scale, -1);
    auto monsters = sp_create("monsters.png", po_monsters, map_scale, 0);
    /* ������ť */
    auto help = sp_create("column_help_normal.png", po_help, 2.3, 0);
    help->setName("help");
    auto monster = sp_create("column_monster_pressed.png", po_monster, map_scale, 0);
    auto tower = sp_create("column_tower_normal.png", po_tower, 2.2, 0);
    tower->setName("tower");
    /* ������Ļ */
    auto monster_1 = sp_create("monster_1.png", po_monster_1, map_scale, 1);
    auto monster_2 = sp_create("monster_2.png", po_monster_2, map_scale, 1);
    auto monster_3 = sp_create("monster_3.png", po_monster_3, map_scale, 1);
    auto speed_1 = sp_create("monster_speed.png", po_speed_1, map_scale, 1);
    auto speed_2 = sp_create("monster_speed.png", po_speed_2, map_scale, 1);
    auto blood_1 = sp_create("monster_blood.png", po_blood_1, map_scale, 1);
    auto blood_2 = sp_create("monster_blood.png", po_blood_2, map_scale, 1);
    auto caption = sp_create("monster_caption.png", po_caption, map_scale, 1);

    /********** ������ť **********/
    /* ���� */
    auto btn_back = btn_create(
        "HelpScene/contents/btn_back_normal.png",
        "HelpScene/contents/btn_back_pressed.png",
        "HelpScene/contents/btn_back_normal.png",
        po_btn_back, 1);

    /********** �����¼� **********/
    /* help */
    auto help_click_listener = EventListenerTouchOneByOne::create();
    help_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("help"));    //�ӳ�����ץȡ��Ϊhelp�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ��
        return false;   //����false����ִֹ���¼���Ӧ
        };
    help_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    help_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = HelpScene_1::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);  
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(help_click_listener, this);

    /* tower */
    auto tower_click_listener = EventListenerTouchOneByOne::create();
    tower_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("tower"));    //�ӳ�����ץȡ��Ϊtower�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ��
        return false;   //����false����ִֹ���¼���Ӧ
        };
    tower_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    tower_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = HelpScene_3::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(tower_click_listener, this);

    return true;
}