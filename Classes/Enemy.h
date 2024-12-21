#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class Enemy:public Sprite {
public://±ãÓÚ¼Ì³Ð
	int hp;
	Sprite* hp_holder;
	Sprite* hp_slider;
	CREATE_FUNC(Enemy);
	virtual bool init() { if (!Sprite::init())return false; return true; }

};








#endif // !__ENEMY__