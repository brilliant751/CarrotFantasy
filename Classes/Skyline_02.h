#pragma once

#ifndef __SKYLINE_02__
#define __SKYLINE_02__

#include "cocos2d.h"

USING_NS_CC;

/* ������ */
class Map_1_02 : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(Map_1_02);

	void update_create(float dt);

private:
	int speed = 1;
	bool is_pause = 0;
	int c_hp = 10;
	int waves = 1;
	int total_waves = 20;
	int money = 120;
};

#endif //!__SKYLINE_02__