
#include "EnterScene.h"
#include "MapChoose.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

//1

/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* mapChoose::create_Scene()
{
    return Scene::create();
}

bool mapChoose::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("demo.jpg");
    if (background == nullptr)
        problemLoading("'demo.jpg'");
    else
    {
        //设置位置
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        background->setScale(1.5f, 2.0f);
        //添加到子代
        this->addChild(background, -1);
    }





    return true;
}