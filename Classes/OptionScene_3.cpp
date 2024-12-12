
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
Scene* OptionScene_3::create_Scene()
{
    return OptionScene_3::create();
}

/* ���ذ�ť�л���StartScene */
void OptionScene_3::back_onButtonClicked(Ref* sender) {
    auto next = StartScene::create_Scene();
    Director::getInstance()->popScene();
}

/* ������ʼ�� */
bool OptionScene_3::init()
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


    constexpr int btnY1 = 800;              //��ť�߶�
    constexpr int btnY2 = 280;              //С��ť�߶�
    constexpr float btn_scale = 1.5f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 po_btn_home(400, 750);      //home��ťλ��
    const Vec2 po_bg(visibleSize / 2);     //��ͼλ��
    const Vec2 po_options(600, btnY1);          //column_optionsλ��
    const Vec2 po_statistics(820, btnY1);       //column_statisticsλ��
    const Vec2 po_producer(1040, btnY1);        //column_producerλ��

    /**************************************/

    /********** �������� **********/
    /* �������� */
    auto bg = sp_create("optionBG3.png", po_bg, map_scale, -1);
    /* �����ɵ������ */
    auto options = sp_create("options_normal.png", po_options, 2.3, 0);
    options->setName("options");
    auto statistics = sp_create("statistics_normal.png", po_statistics, 2.3, 0);
    statistics->setName("statistics");
    auto producer = sp_create("producer_pressed.png", po_producer, map_scale, 0);

    /********** ������ť **********/
    /* ���� */
    auto btn_back = btn_create(
        "OptionScene/contents/option_1_back_normal.png",
        "OptionScene/contents/option_1_back_pressed.png",
        "OptionScene/contents/option_1_back_normal.png",
        po_btn_home, 1);

    /********** �����¼� **********/
    /* statistics */
    auto statistics_click_listener = EventListenerTouchOneByOne::create();
    statistics_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("statistics"));    //�ӳ�����ץȡ��Ϊstatistics�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ��
        return false;   //����false����ִֹ���¼���Ӧ
        };
    statistics_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    statistics_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_2::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(statistics_click_listener, this);

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

    return true;
}