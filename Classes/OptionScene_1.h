#pragma once

#ifndef __Option_Scene_1__
#define __Option_Scene_1__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class OptionScene_1 : public Scene
{
public:
	// 创建一个场景
	static Scene* create_Scene();

	// 初始化
	virtual bool init();

	void back_onButtonClicked(Ref* sender);
	void reset_onButtonClicked(Ref* sender);

	CREATE_FUNC(OptionScene_1);

};
/* 重置确认弹窗 */
class PopReset : public Layer
{
public:
	// 创建一个层
	static Layer* create_Layer();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(PopReset);
};

#endif