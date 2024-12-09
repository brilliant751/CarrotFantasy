#include "EnterScene.h"
#include "MapChoose.h"
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
Scene* OptionScene_1::create_Scene()
{
    return OptionScene_1::create();
}


/* ���ذ�ť�л���StartScene */
void OptionScene_1::back_onButtonClicked(Ref* sender) {
    Director::getInstance()->popScene();
}

/* ������ʼ�� */
bool OptionScene_1::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("OptionScene/OptionScene_1.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("OptionScene/OptionScene_2.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("OptionScene/OptionScene_3.plist");

    /* ��������ıհ����� */
    //lambda����ʽ
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
    //lambda����ʽ
    //normal_name��   ����״̬��ͼ���е�����
    //pressed_name��  ѡ��״̬��ͼ���е�����
    //locked_name��   ���ɵ��״̬��ͼ���е����� 
    //pos��           ����
    //scale��         �Ŵ���
    //layer��         ���ò���
    //btn_type:       ��ť���
    //                         1 - ѡ��
    //                         2 - ����ͳ��
    //                         3 - ������
    //                         4 - Home
    /* ������ť�ıհ����� */
    //lambda����ʽ
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
    constexpr float btn_scale = 1.5f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 options_btn(540, btnY1);          //ѡ�ť
    const Vec2 statistics_btn(980, btnY1);        //����ͳ�ư�ť
    const Vec2 producer_btn(1400, btnY1);       //��������ť
    const Vec2 sound_btn(540, btnY2);          //��Ч��ť
    const Vec2 BGM_btn(980, btnY2);        //�������ְ�ť
    const Vec2 reset_btn(1400, btnY2);       //������Ϸ��ť
    const Vec2 reset_yes_btn(540, btnY2);          //ȷ�ϰ�ť
    const Vec2 reset_no_btn(980, btnY2);        //ȡ����ť
    const Vec2 po_btn_home(360, 920);      //home��ťλ��
    const Vec2 po_sound_effect(550, 800);     //��Ч ��Ļλ�� 
    const Vec2 po_BGM(980, 800);     //BGM ��Ļλ��

    /**************************************/

       /* ������Ļ */
    auto word_sound_effect = sp_create("word_sound_effect.png", po_sound_effect, map_scale, 1);
    auto word_BGM = sp_create("word_BGM.png", po_BGM , map_scale, 1);

    /* ���� ѡ�� ��ť */
    auto Options = btn_create(
        "OptionScene_1/contents/options_normal.png",
        "OptionScene_1/contents/options_pressed.png",
        options_btn, btn_scale);
    /* ���� ����ͳ�� ��ť */
    auto Statistics = btn_create(
        "OptionScene_1/contents/statistics_normal.png",
        "OptionScene_1/contents/statistics_pressed.png",
        statistics_btn, btn_scale);
    /* ���� ������ ��ť */
    auto Producer= btn_create(
        "OptionScene_1/contents/producer_normal.png",
        "OptionScene_1/contents/producer_pressed.png",
        producer_btn, btn_scale);
    /* ���� ������Ч ��ť */
    auto sound_effect = btn_create(
        "OptionScene_1/contents/sound_effect_open.png",
        "OptionScene_1/contents/sound_effect_close.png",
        sound_btn, btn_scale);
    /* ���� ������������ ��ť */
    auto BGM = btn_create(
        "OptionScene_1/contents/BGM_open.png",
        "OptionScene_1/contents/BGM_close.png",
        BGM_btn, btn_scale);
    /* ���� ������Ϸ ��ť */
    auto reset1 = btn_create(
        "OptionScene_1/contents/reset_normal.png",
        "OptionScene_1/contents/reset_pressed.png",
        reset_btn, btn_scale);
    /* ���� ������Ϸȷ�� ��ť */
    auto reset2 = btn_create(
        "OptionScene_1/contents/reset_yes_normal.png",
        "OptionScene_1/contents/reset_yes_pressed.png",
        reset_yes_btn, btn_scale);
    /* ���� ������Ϸȡ�� ��ť */
    auto reset3 = btn_create(
        "OptionScene_1/contents/reset_no_normal.png",
        "OptionScene_1/contents/reset_no_pressed.png",
        reset_no_btn, btn_scale);
    /* ���� */
    auto btn_back = btn_create(
        "OptionScene_1/contents/option_1_back_normal.png",
        "OptionScene_1/contents/option_1_back_pressed.png",
        po_btn_home, 3);

    /************     ����     ************/

    const Vec2 po_bg(visibleSize / 2);     //��ͼλ��
    const Vec2 po_bg_bottom(1000, 150);    //bg_bottomλ��
    //constexpr float btn_scale = 1.1f;      //��ť�Ŵ���
    //constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 po_btn_back(360, 920);      //home��ťλ��
    const Vec2 po_options(750, 922);          //column_optionsλ��
    const Vec2 po_statistics(980, 920);       //column_statisticsλ��
    const Vec2 po_producer(1190, 925);        //column_producerλ��

    /**************************************/

    /********** �������� **********/
    /* �������� */
    auto bg = sp_create("optionBG1.png", po_bg, map_scale, -1);

    /* �����ɵ������ */
    auto options = sp_create("statistics_pressed.png", po_options, map_scale, 0);
    auto statistics = sp_create("statistics_normal.png", po_statistics, 2.3, 0);
    statistics->setName("statistics");
    auto producer = sp_create("producer_normal.png", po_producer, 2.2, 0);
    producer->setName("producer");

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

    /* sound_effect */
    auto sound_effect_click_listener = EventListenerTouchOneByOne::create();
    sound_effect_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("sound_effect"));    //�ӳ�����ץȡ��Ϊsound_effect�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ�� and ��ǰΪ��һ������
        return false;   //����false����ִֹ���¼���Ӧ
        };
    sound_effect_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    sound_effect_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_3::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sound_effect_click_listener, this);

    /* BGM */
    auto BGM_click_listener = EventListenerTouchOneByOne::create();
    BGM_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("BGM"));    //�ӳ�����ץȡ��ΪBGM�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ�� and ��ǰΪ��һ������
        return false;   //����false����ִֹ���¼���Ӧ
        };
    BGM_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    BGM_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_3::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(BGM_click_listener, this);

    return true;
}