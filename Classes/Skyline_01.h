#pragma once

#ifndef __SKYLINE_01__
#define __SKYLINE_01__

#include "cocos2d.h"
#include "tools.h"

USING_NS_CC;
using namespace std;

/* 主场景 */
class Map_1_01 : public Scene
{
	friend void update_tag(int& tag, int waves);
public:
	// 创建一个场景
	static Scene* create_Scene();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(Map_1_01);

	// 定时刷新类函数
	void create_monster(float dt);	//创建怪物
	void update_create(float dt);	//刷新建造按钮

private:
	const int total_waves = 15;		//总波次
	int c_hp = 10;			//萝卜生命值
	bool is_pause = 0;		//是否暂停
	int money = 120;		//金钱
	int waves = 1;			//波次

	/* 创建怪物参数 */
	Vec2 pos;
	float mons_scale = 1.5f;
	string mons_url[16] = { "", "Monster01_0.png" };
	//    XX     XX      XX
	// 关卡序号 波次 第几个怪物
	int mons_tag = 10101;

};

#endif //!__SKYLINE_01__