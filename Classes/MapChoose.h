#pragma once

#ifndef __MAP_CHOOSE__
#define __MAP_CHOOSE__

#include "cocos2d.h"

USING_NS_CC;

class mapChoose : public Scene
{
public:
	static Scene* create_Scene();

	virtual bool init();

	CREATE_FUNC(mapChoose);
};

#endif // !__MAP_CHOOSE__

