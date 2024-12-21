#pragma once

#ifndef __TOWERS__
#define __TOWERS__

#include "cocos2d.h"

#include "Towers_info.h"
#include "Monsters.h"
#include "Skyline_01.h"
#include "tools.h"

using namespace std;

USING_NS_CC;

class Tower :public cocos2d::Sprite {
public:
	// 创建防御塔
	static Tower* create_Tower(int type, int line, int row, Scene* scene);

	// 初始化
	virtual bool init();

	// 设置防御塔类型
	void setType(tower_info type) { info = type; }

	void up_level();

	// 设置位置
	void _setPosition(const Vec2& pos);

	void _setSpriteFrame();

	void _setScale(const float& building_scale, const float& base_scale, const float& bullet_scale);

	int get_up_money() { return info.cost[level + 1]; }
	int get_sell_money() { return info.sell[level]; }
	int get_level() { return level; }
	float get_scale() { return info.scale[level]; }
	//void _setZOrder()
	void remove() {
		base->removeFromParentAndCleanup(true);
		this->removeFromParentAndCleanup(true);
	}
	float get_range() { return info.radius[level]; };
	float get_angle() { return angle; };
	string get_bullet_url() { return info.bullet_url[level]; };

	Monster* get_first_monster();
	int tower_rotate_direction();
	void tower_rotate_1(float dt);
	void shoot_3(float dt);
	void biu_fan(Vec2& start, float x, float y);



	// 定义create
	CREATE_FUNC(Tower);
private:
	tower_info info;
	Sprite* base;
	Sprite* bullet;
	int level = 0;
	float angle = 0;
};




#endif // !__TOWERS__