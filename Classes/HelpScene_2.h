#pragma once

#ifndef __Help_Scene_2__
#define __Help_Scene_2__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


class HelpScene_2 : public Scene
{
public:
	static Scene* create_Scene();
	virtual bool init();

	void back_onButtonClicked(Ref* sender);

	CREATE_FUNC(HelpScene_2);
private:
	
};

#endif // !__Help_Scene_2__

