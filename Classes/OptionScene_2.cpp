
#include "StartScene.h"
#include "OptionScene_1.h"
#include "OptionScene_2.h"
#include "OptionScene_3.h"
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
Scene* OptionScene_2::create_Scene()
{
    return OptionScene_2::create();
}

/* ���ذ�ť�л���StartScene */
void OptionScene_2::back_onButtonClicked(Ref* sender) {
    auto next = StartScene::create_Scene();
    Director::getInstance()->popScene();
}

/* ������ʼ�� */
bool OptionScene_2::init()
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
    const Vec2 po_bg_bottom(1000, 150);    //bg_bottomλ��
    constexpr float btn_scale = 1.1f;      //��ť�Ŵ���
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 po_btn_home(360, 920);      //home��ťλ��
    const Vec2 po_options(750, 922);          //column_optionsλ��
    const Vec2 po_statistics(980, 920);       //column_statisticsλ��
    const Vec2 po_producer(1190, 925);        //column_producerλ��
    const Vec2 po_adventure_mode(550, 480);     //��Ч ��Ļλ�� 
    const Vec2 po_hide_levels(980, 480);     //BGM ��Ļλ��
    const Vec2 po_boss_mode(1400, 480);    //BOSSģʽ ��Ļλ�� 
    const Vec2 po_all_items(757, 412);       //�ݻٵ��� ��Ļλ�� 
    const Vec2 po_all_money(550, 480);     //��Ǯ�� ��Ļλ�� 
    const Vec2 po_all_monsters(980, 480);     //��ܹ�����Ŀ ��Ļλ��
    const Vec2 po_all_bosses(1400, 480);    //���BOSS��Ŀ ��Ļλ�� 
    const Vec2 po_all_items(757, 412);       //�ݻٵ��� ��Ļλ�� 
    const Vec2 po_map_1(757, 350);       //ð�յ�ͼ��Ŀ ��Ļλ�� 
    const Vec2 po_map_2(1177, 412);      //���ص�ͼ��Ŀ ��Ļλ�� 
    const Vec2 po_map_3(1177, 350);      //BOSS��ͼ��Ŀ ��Ļλ�� 

    /**************************************/

    /********** �������� **********/
    /* �������� */
    auto bg = sp_create("optionBG2.png", po_bg, map_scale, -1);
    /* �����ɵ������ */
    auto options = sp_create("statistics_pressed.png", po_options, map_scale, 0);
    options->setName("options");
    auto statistics = sp_create("statistics_normal.png", po_statistics, 2.3, 0);
    auto producer = sp_create("producer_normal.png", po_producer, 2.2, 0);
    producer->setName("producer");
    /* ������Ļ */
    auto adventure_mode = sp_create("adventure_mode.png", po_adventure_mode, map_scale, 1);
    auto hide_levels = sp_create("hide_levels.png", po_hide_levels, map_scale, 1);
    auto boss_mode = sp_create("boss_mode.png", po_boss_mode, map_scale, 1);
    auto all_money = sp_create("all_money.png", po_all_money, map_scale, 1);
    auto all_monsters = sp_create("all_monsters.png", po_all_monsters, map_scale, 1);
    auto all_bosses = sp_create("all_bosses.png", po_all_bosses, map_scale, 1);
    auto all_items = sp_create("all_items.png", po_all_items, map_scale, 1);
    auto map_1 = sp_create("option_map.png", po_map_1, map_scale, 1);
    auto map_2 = sp_create("option_map.png", po_map_2, map_scale, 1);
    auto map_3 = sp_create("option_map.png", po_map_3, map_scale, 1);

    /********** ������ť **********/
    /* ���� */
    auto btn_back = btn_create(
        "OptionScene_1/contents/option_1_back_normal.png",
        "OptionScene_1/contents/option_1_back_pressed.png",
        "OptionScene_1/contents/option_1_back_normal.png",
        po_btn_home, 3);

    /********** �����¼� **********/
    /* options */
    auto options_click_listener = EventListenerTouchOneByOne::create();
    options_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("options"));    //�ӳ�����ץȡ��Ϊhelp�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ��
        return false;   //����false����ִֹ���¼���Ӧ
        };
    options_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    options_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_1::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(options_click_listener, this);

    /* producer */
    auto producer_click_listener = EventListenerTouchOneByOne::create();
    producer_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("producer"));    //�ӳ�����ץȡ��Ϊproducer�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ�� and ��ǰΪ��һ������
        return false;   //����false����ִֹ���¼���Ӧ
        };
    producer_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    producer_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_3::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(producer_click_listener, this);

    return true;
}