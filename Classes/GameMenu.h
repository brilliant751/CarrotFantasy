#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;

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

/* 可攻击对象 */
class Target : public Sprite
{
public:
	double hp;	//血量
	double max_hp;	//血量
	Sprite* selected;	//锁定标识
	Sprite* hp_holder;	//血条槽
	LoadingBar* hp_slider;	//血条

	CREATE_FUNC(Target);
	void setHP(int max_hp) { this->max_hp = hp = max_hp; }
	virtual void create_slider();
	virtual void get_hurt(int damage)
	{
		hp -= damage;
		float percent = hp / max_hp * 100;
		hp_slider->setPercent(percent);
	}

	// 获取锁定标识
	Sprite* get_selected_sprite()const { return selected; }
};




#endif // !__GAME_MENU__