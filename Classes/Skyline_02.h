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


};

#endif //!__SKYLINE_02__