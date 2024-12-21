#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class Enemy:public Sprite {
public://±ãÓÚ¼Ì³Ð
	int hp = 1000;
	Sprite* hp_holder;
	Sprite* hp_slider;


	virtual bool init() { if (!Sprite::init())return false; return true; }
	CREATE_FUNC(Enemy);
};








#endif // !__ENEMY__