
#include "EnterScene.h"
#include "StartScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "MapChoose.h"

USING_NS_CC;
using namespace ui;
using namespace std;

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
    static const auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("theme_desert.png");

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
    constexpr float stage_scale = 1.0f;     //�½ڷŴ���
    constexpr float btn_scale = 1.1f;       //��ť�Ŵ���
    const float btnY = visibleSize.y / 2;   //��ť�߶�
    const Vec2 bg(visibleSize / 2);         //�½�λ��
    const Vec2 btn_left(400, btnY);         //����λ��
    const Vec2 btn_right(1560, btnY);       //����λ��

    /**************************************/

    /* �����¼� */
    auto click_listener = EventListenerTouchOneByOne::create();
    click_listener->onTouchBegan = [&](Touch* touch, Event* event) { 
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("skyline"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = MapChoose::create_Scene();
        if (next == nullptr)
            return false;
        
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, this);

    /* �������� */
    auto background = sp_create("bg.png", bg, bg_scale, -1);

    /* �����½� */
    auto skyline = sp_create("theme_skyline.png", bg, stage_scale, 1);
    //skyline->initWithSpriteFrameName("theme_desert.png");
    skyline->setName("skyline");
    //skyline->setSpriteFrame(frame);


    /******* ������ť *******/
    /* ��ť�������� */
    auto goleft = btn_create(
        "EnterScene/contents/left_normal.png",
        "EnterScene/contents/left_pressed.png",
        btn_left, btn_scale);

    
    /* ��ť�������� */
    auto goright = btn_create(
        "EnterScene/contents/right_normal.png",
        "EnterScene/contents/right_pressed.png",
        btn_right, btn_scale);
    //ToDo
    auto func = [&](Ref* eSender, Widget::TouchEventType type) {
        auto sp = (Sprite*)(this->getChildByName("skyline"));
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                //skyline->setSpriteFrame(frame);
                sp->setTexture("EnterScene/contents/theme_jungle.png");
                break;
            default:
                break;
        }
        };
    goright->addTouchEventListener(func);


    return true;
}
