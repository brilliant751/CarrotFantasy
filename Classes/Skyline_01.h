#pragma once

#ifndef __SKYLINE_01__
#define __SKYLINE_01__

#include "cocos2d.h"

USING_NS_CC;

/* ������ */
class Map_1_01 : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(Map_1_01);

	bool is_popup = false;

};

#endif //!__SKYLINE_01__