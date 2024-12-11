
#include "EnterScene.h"
#include "StartScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "MapChoose.h"

USING_NS_CC;
using namespace ui;
using namespace std;

static int top = 0;    // ջ��ָ��

/* ����ļ��޷��򿪣���ӡ������Ϣ */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* Enter::create_Scene()
{
	return Enter::create();
}

/* �����ͼѡ����� */
void chooseCall(Ref* pSender)
{
    auto map_choose = MapChoose::create_Scene();
    Director::getInstance()->replaceScene(map_choose);
}

bool Enter::init()
{
	if (!Scene::init())
		return false;

    const Vec2 visibleSize = Vec2(Director::getInstance()->getVisibleSize());
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Ԥ���ؾ���ͼ��
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("EnterScene/EnterScene.plist");

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

    constexpr float bg_scale = 1.5f;        //�����Ŵ���
    constexpr float stage_scale = 1.3f;     //�½ڷŴ���
    constexpr float btn_scale = 1.3f;       //��ť�Ŵ���
    const float btnY = visibleSize.y / 2;   //��ť�߶�
    const Vec2 bg(visibleSize / 2);         //����λ��
    const Vec2 stg(810, 460);               //�½�λ��
    const Vec2 btn_left(370, btnY);         //����λ��
    const Vec2 btn_back(305, 823);          //���ذ�ťλ��
    const Vec2 btn_right(1250, btnY);       //����λ��

    /**************************************/

    /* �����¼� */
    auto click_listener = EventListenerTouchOneByOne::create();
    click_listener->onTouchBegan = [&](Touch* touch, Event* event) { 
        auto pos = touch->getLocation();    //��ȡ���λ��
        auto sp = (Sprite*)(this->getChildByName("stages"));    //�ӳ�����ץȡ��Ϊstages�ľ���
        if (sp->getBoundingBox().containsPoint(pos) && top == 0)
            return true;    //���λ���ھ��鷶Χ�� and ��ǰΪ��һ������
        return false;   //����false����ִֹ���¼���Ӧ
        };
    click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = MapChoose::create_Scene();
        if (next == nullptr)
            return false;   //ȷ��next�ǿ�
        Director::getInstance()->pushScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, this);

    /* �������� */
    auto background = sp_create("bg.png", bg, bg_scale, -1);

    /* �����½� */
    auto stages = sp_create("theme_skyline.png", stg, stage_scale, 1);
    stages->setName("stages");  //�������֣�����ץȡ


    /******* ������ť *******/
    /* ��ť�������� */
    auto goleft = btn_create(
        "EnterScene/contents/left_normal.png",
        "EnterScene/contents/left_pressed.png",
        btn_left, btn_scale);
    goleft->addTouchEventListener([&](Ref* eSender, Widget::TouchEventType type) {
        auto sp = (Sprite*)(this->getChildByName("stages"));    //ץȡ����
        //����
        const string themes[3] = { "theme_skyline.png", "theme_desert.png", "theme_jungle.png" };
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                if (top > 0)
                    sp->setSpriteFrame(themes[--top]);
                break;
            default:
                break;
        }
        });

    
    /* ��ť�������� */
    auto goright = btn_create(
        "EnterScene/contents/right_normal.png",
        "EnterScene/contents/right_pressed.png",
        btn_right, btn_scale);
    goright->addTouchEventListener([&](Ref* eSender, Widget::TouchEventType type) {
        auto sp = (Sprite*)(this->getChildByName("stages"));    //ץȡ����
        //����
        const string themes[3] = { "theme_skyline.png", "theme_desert.png", "theme_jungle.png" };
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                if (top < 2)
                    sp->setSpriteFrame(themes[++top]);
                break;
            default:
                break;
        }
        });

    /* ��ť�������� */
    auto back_btn = btn_create(
        "EnterScene/contents/home_normal.png",
        "EnterScene/contents/home_pressed.png",
        btn_back, bg_scale, 3);
    back_btn->addTouchEventListener([&](Ref* eSender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                Director::getInstance()->popScene();
                break;
            default:
                break;
        }
        });


    return true;
}
