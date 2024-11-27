
#include "StartScene.h"
#include "EnterScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* StartScene::create_Scene()
{
	return StartScene::create();
}

static void enterCall(Ref* eSender)
{
    auto next = Enter::create_Scene();
    Director::getInstance()->replaceScene(next);
}

/* ����ļ��޷��򿪣���ӡ������Ϣ */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* ��ʼ������ */
bool StartScene::init()
{
    // ��ʹ�û���ĳ�ʼ������
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����رհ�ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(StartScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // ����������Ϸ��ť
    auto enterBtn = Button::create(
        "StartScene/front_btn_start_normal.png",
        "StartScene/front_btn_start_pressed.png",
        "StartScene/front_btn_start_pressed.png");
    enterBtn->setPosition(Vec2(504, 456));

    enterBtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                enterCall(this);
                break;
            default:
                break;
        }
        });

    addChild(enterBtn);

    // �����˵�
    //auto menu = Menu::create(enterBtn, NULL);
    //menu->setPosition(Vec2(500, 500));
    //this->addChild(menu, 1);

    /* �������� */
    auto background = Sprite::create("StartScene/front_bg.png");
    if (background == nullptr)
        problemLoading("'StartScene/front_bg.png'");
    else
    {
        //����λ��
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        //��ӵ��Ӵ�
        addChild(background, -1);
    }

    return true;
}

/* �رս��棬�˳����� */
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

