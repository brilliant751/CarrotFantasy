#pragma once

#ifndef __SKYLINE_01__
#define __SKYLINE_01__

#include "cocos2d.h"

USING_NS_CC;

class Map_1_01 : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();


	CREATE_FUNC(Map_1_01);

};

#endif //!__SKYLINE_01__