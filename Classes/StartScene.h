#pragma once

#ifndef __START_SCENE_MENU__
#define __START_SCENE_MENU__

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public Scene
{
public:
	// 创建一个场景
	static Scene* create_Scene();

	// 初始化
	virtual bool init();

	// 关闭程序
	void menuCloseCallback(Ref* pSender);


	CREATE_FUNC(StartScene);

};

#endif