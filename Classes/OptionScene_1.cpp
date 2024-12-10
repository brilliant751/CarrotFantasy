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
//����������
class PopupLayer : public cocos2d::Layer {
public:
    static PopupLayer* createlayer();
    virtual bool init();
    CREATE_FUNC(PopupLayer);
};

PopupLayer* PopupLayer::createlayer() {
    auto layer = PopupLayer::createlayer();
    return layer;
}

bool PopupLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    // ����һ��ȫ���ĻҰ�����Ϊ����
    auto dimLayer = LayerColor::create(Color4B(0, 0, 0, 128), Director::getInstance()->getVisibleSize().width,
        Director::getInstance()->getVisibleSize().height);
    this->addChild(dimLayer);
    // ��ӵ������ݣ����ı�����ť��
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

    const Vec2 reset_yes_btn(540, 440);          //ȷ�ϰ�ť
    const Vec2 reset_no_btn(980, 440);        //ȡ����ť
    constexpr float btn_scale = 1.5f;       //��ť�Ŵ���
    /**************************************/

       /* ���� ������Ϸȷ�� ��ť */
    auto reset2 = btn_create(
        "OptionScene/contents/reset_yes_normal.png",
        "OptionScene/contents/reset_yes_pressed.png",
        reset_yes_btn, btn_scale);
    /* ���� ������Ϸȡ�� ��ť */
    auto reset3 = btn_create(
        "OptionScene/contents/reset_no_normal.png",
        "OptionScene/contents/reset_no_pressed.png",
        reset_no_btn, btn_scale);

    reset3->addClickEventListener([](Ref* sender) {
        // ����ǲ㣨Layer�����Ӹ��ڵ��Ƴ�����
        if (auto layer = dynamic_cast<Layer*>(sender)) {
            layer->removeFromParent();
        }
        });
    this->addChild(reset3);
    return true;
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
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 options_btn(540, btnY1);          //ѡ�ť
    const Vec2 statistics_btn(980, btnY1);        //����ͳ�ư�ť
    const Vec2 producer_btn(1400, btnY1);       //��������ť
    const Vec2 sound_btn(850, 700);          //��Ч��ť
    const Vec2 BGM_btn(1250, 700);        //�������ְ�ť
    const Vec2 reset_btn(1025, 500);       //������Ϸ��ť
    const Vec2 po_btn_home(440, 960);      //home��ťλ��
    const Vec2 po_sound_effect(840, 800);     //��Ч ��Ļλ�� 
    const Vec2 po_BGM(1240, 800);     //BGM ��Ļλ��
    const Vec2 po_bg(visibleSize / 2);     //��ͼλ��
    const Vec2 po_bg_bottom(1000, 150);    //bg_bottomλ��
    const Vec2 po_options(750, 922);          //column_optionsλ��
    const Vec2 po_statistics(980, 920);       //column_statisticsλ��
    const Vec2 po_producer(1190, 925);        //column_producerλ��


    /**************************************/

       /* ������Ļ */
    auto word_sound_effect = sp_create("word_sound_effect.png", po_sound_effect, map_scale, 1);
    auto word_BGM = sp_create("word_BGM.png", po_BGM , map_scale, 1);

    /* ���� ѡ�� ��ť */
    auto Options_btn = btn_create(
        "OptionScene/contents/options_normal.png",
        "OptionScene/contents/options_pressed.png",
        options_btn, btn_scale);
    /* ���� ����ͳ�� ��ť */
    auto Statistics_btn = btn_create(
        "OptionScene/contents/statistics_normal.png",
        "OptionScene/contents/statistics_pressed.png",
        statistics_btn, btn_scale);
    /* ���� ������ ��ť */
    auto Producer_btn= btn_create(
        "OptionScene/contents/producer_normal.png",
        "OptionScene/contents/producer_pressed.png",
        producer_btn, btn_scale);
    /* ���� ������Ч ��ť */
    auto sound_effect_btn = btn_create(
        "OptionScene/contents/sound_effect_open.png",
        "OptionScene/contents/sound_effect_close.png",
        sound_btn, btn_scale);
    /* ���� ������������ ��ť */
    auto btn_BGM = btn_create(
        "OptionScene/contents/BGM_open.png",
        "OptionScene/contents/BGM_close.png",
        BGM_btn, btn_scale);
    /* ���� ������Ϸ ��ť */
    auto reset1_btn = btn_create(
        "OptionScene/contents/reset_normal.png",
        "OptionScene/contents/reset_pressed.png",
        reset_btn, btn_scale);
    /* ���� */
    auto btn_back = btn_create(
        "OptionScene/contents/option_1_back_normal.png",
        "OptionScene/contents/option_1_back_pressed.png",
        po_btn_home, 1.5);


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
    auto reset1 = sp_create("reset_normal.png", reset_btn, 2.2, 0);
    reset1->setName("reset1");


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
    /* reset1 */
    auto reset1_click_listener = EventListenerTouchOneByOne::create();
    reset1_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("reset1"));    //�ӳ�����ץȡ��Ϊreset1�ľ���
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //���λ���ھ��鷶Χ��
        return false;   //����false����ִֹ���¼���Ӧ
        };
    statistics_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    statistics_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto resetpopupLayer = PopupLayer::create();
        if (auto scene = Director::getInstance()->getRunningScene()) {
            scene->addChild(resetpopupLayer);
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(reset1_click_listener, this);


    return true;
}