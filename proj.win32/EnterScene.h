#pragma once


#ifndef __ENTER_SCENE__
#define __ENTER_SCENE__

#include "cocos2d.h"

USING_NS_CC;

class Enter : public Scene
{
public:
	static Scene* create_Scene();

	virtual bool init();

	CREATE_FUNC(Enter);
};

#endif // !__ENTER_SCENE__
