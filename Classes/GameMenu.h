#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"
#include "ui/cocosGUI.h"
//#include "monsters.h"

USING_NS_CC;
using namespace ui;
using namespace std;

#define BARRIER_TARGET 0
#define MONSTER_TARGET 1

class Monster;

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
	double hp;		//血量
	double max_hp;	//最大血量
	int reward = 200;		//掉落金币
	Sprite* selected;		//锁定标识
	Sprite* hp_holder;		//血条槽
	LoadingBar* hp_slider;	//血条

	// 设置血量
	void setHP(int max_hp) { this->max_hp = hp = max_hp; }
	// 获取类型
	virtual int get_type()const { return BARRIER_TARGET; }
	// 创建血条
	virtual void create_slider();
	// 受到伤害
	virtual void get_hurt(int damage);

	// 获取锁定标识
	Sprite* get_selected_sprite()const { return selected; }
	// 定义create
	CREATE_FUNC(Target);
};




#endif // !__GAME_MENU__