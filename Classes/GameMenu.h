#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"
using namespace std;

USING_NS_CC;

/* 弹窗菜单 */
class PauseMenu : public Layer
{
public:
	// 创建一个层
	static Layer* create_Layer();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(PauseMenu);
};


/* 倒计时 */
class CountDown : public Layer {
public:
	// 创建一个层
	static Layer* create_Layer();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(CountDown);
private:
	Sprite* count;
	string count_url[3] = {
		"start_time_1.png","start_time_2.png","start_time_3.png"
	};
	int co = 2;


};
#endif // !__GAME_MENU__