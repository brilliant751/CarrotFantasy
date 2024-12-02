#pragma once

#ifndef __MAP_CHOOSE__
#define __MAP_CHOOSE__

#include "cocos2d.h"

USING_NS_CC;

class MapChoose : public Scene
{
public:
	static Scene* create_Scene();

	virtual bool init();

	CREATE_FUNC(MapChoose);
};

#endif // !__MAP_CHOOSE__

