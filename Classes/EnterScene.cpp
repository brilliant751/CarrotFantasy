
#include "EnterScene.h"
#include "StartScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include"MapChoose.h"

USING_NS_CC;
using namespace ui;

/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* Enter::create_Scene()
{
	return Enter::create();
}

/* 进入地图选择界面 */
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

    /* 创建背景 */
    auto background = Sprite::create("demo.jpg");
    if (background == nullptr)
        problemLoading("'demo.jpg'");
    else
    {
        //设置位置
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        //background->setPosition(Vec2(500, 400));
        //background->setPosition(Vec2(1000, 1000));
        background->setScale(1.5f, 2.0f);
        //添加到子代
        this->addChild(background);
    }

    /******* 创建按钮 *******/
    /* 按钮——选择章节 */
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

    /* 按钮——左移 */
    auto goleft = Button::create();
    //ToDo
    
    /* 按钮——右移 */
    auto goright = Button::create();
    //ToDo


    return true;
}
