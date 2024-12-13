#pragma once

#ifndef __MONSTERS__
#define __MONSTERS__

#include "cocos2d.h"

#include "Monster_info.h"

using namespace std;

USING_NS_CC;

class Monster : public cocos2d::Sprite
{
public:
	// 创建怪物
	static Monster* create_Monster(monf type);
	// 初始化
	virtual bool init();
	// 重写更新函数
	void update(float dt) override;
	// 定义create
	CREATE_FUNC(Monster);
	
private:
	monf info;	//怪物属性
	// 设置怪物类型
	void setType(monf type) { info = type; }
};

#endif // !__MONSTERS__

