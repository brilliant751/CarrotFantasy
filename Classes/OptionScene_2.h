#pragma once

#ifndef __Option_Scene_2__
#define __Option_Scene_2__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


class OptionScene_2 : public Scene
{
public:
	static Scene* create_Scene();
	virtual bool init();

	void back_onButtonClicked(Ref* sender);

	CREATE_FUNC(OptionScene_2);
private:

};

#endif // !__Option_Scene_2__

