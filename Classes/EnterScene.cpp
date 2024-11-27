
#include "EnterScene.h"
#include "StartScene.h"
#include "AudioEngine.h"

USING_NS_CC;

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

bool Enter::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* 创建背景 */
    auto background = Sprite::create("MainMenu.png");
    if (background == nullptr)
        problemLoading("'HelloWorld.png'");
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


    return true;
}
