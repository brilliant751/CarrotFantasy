#pragma once

#ifndef __SKYLINE_01__
#define __SKYLINE_01__

#include "cocos2d.h"

USING_NS_CC;

/* 主场景 */
class Map_1_01 : public Scene
{
public:
	// 创建一个场景
	static Scene* create_Scene();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(Map_1_01);

private:
	int speed = 1;
	bool is_pause = 0;
	int c_hp = 10;
	int waves = 1;
	int total_waves = 15;
};

#endif //!__SKYLINE_01__