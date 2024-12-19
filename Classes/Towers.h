#pragma once

#ifndef __TOWERS__
#define __TOWERS__

#include "cocos2d.h"

#include "Towers_info.h"

using namespace std;

USING_NS_CC;

class Tower :public cocos2d::Sprite {
public:
	// 创建防御塔
	static Tower* create_Tower(int type,int line,int row,Scene* scene);

	// 初始化
	virtual bool init();

	// 设置防御塔类型
	void setType(tower_info type) { info = type; }

	void up_level();

	// 设置位置
	void _setPosition(const Vec2& building_pos,const Vec2& base_pos);

	void _setSpriteFrame(const string& building_url, const string& base_url);

	void _setScale(const float& building_scale, const float& base_scale);

	int get_up_money() { return info.cost[level + 1]; }
	int get_sell_money() { return info.sell[level]; }
	int get_level() { return level; }
	float get_scale() { return info.scale[level]; }
		//void _setZOrder()
	void remove() {
		base->removeFromParentAndCleanup(true);
		this->removeFromParentAndCleanup(true);
	}

	// 定义create
	CREATE_FUNC(Tower);
private:
	tower_info info;
	Sprite* base;
	int level = 0;
	//Sprite* building;

};




#endif // !__TOWERS__