
#include "EnterScene.h"
#include "StartScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include"MapChoose.h"

USING_NS_CC;
using namespace ui;

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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* �������� */
    auto background = Sprite::create("demo.jpg");
    if (background == nullptr)
        problemLoading("'demo.jpg'");
    else
    {
        //����λ��
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        //background->setPosition(Vec2(500, 400));
        //background->setPosition(Vec2(1000, 1000));
        background->setScale(1.5f, 2.0f);
        //��ӵ��Ӵ�
        this->addChild(background);
    }

    /******* ������ť *******/
    /* ��ť����ѡ���½� */
    auto chapterBtn = Button::create(
        "HelloWorld.png",
        "HelloWorld.png");
    chapterBtn->setPosition(Vec2(504, 400));

    chapterBtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                chooseCall(this);
                break;
            default:
                break;
        }
        });

    addChild(chapterBtn, 2);

    /* ��ť�������� */
    auto goleft = Button::create();
    //ToDo
    
    /* ��ť�������� */
    auto goright = Button::create();
    //ToDo


    return true;
}
