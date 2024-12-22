#pragma once

#ifndef __MONSTERS__
#define __MONSTERS__

#include "cocos2d.h"

#include "Monster_info.h"
#include "GameMenu.h"

using namespace std;

USING_NS_CC;

#define MONS_NUM 10     //怪物数量 / 波
#define MAX_WAVE 3

class Monster : public Target
{
public:
	// 创建怪物
	static Monster* create_Monster(monf type, const Vec2* path, const int& top);
	// 初始化
	virtual bool init();
	// 返回类型
	virtual int get_type()const { return MONSTER_TARGET; }
	// 创建血条
	void create_slider();
	// 重写更新函数
	void update(float dt) override;
	// 设置路线
	void set_route(const Vec2* path, const int& top) { route = path; this->top = top; }
	// 定义create
	CREATE_FUNC(Monster);
	
private:
	monf info;	//怪物属性

	/* 行走路线参数 */
	const Vec2* route;	//路线数组指针
	int rt = 1;		//栈顶指针
	int top;		//栈顶位置
	int mons_tag;	//怪物标签

	// 设置怪物类型
	void setType(monf type) { info = type; }
};




#endif // !__MONSTERS__

