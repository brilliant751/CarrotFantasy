#pragma once

#ifndef __monsters__
#define __monsters__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


struct monster_info {
	int type;                                     //记录怪物种类
	int hp;                                       //记录怪物血量
	int speed;                                    //记录怪物移动速度
	int coin;                                     //携带萝卜币
	int damage;                                   //对萝卜造成的伤害
	int count;                                    //走过的格子数


};



class monster : public cocos2d::Sprite
{
public:

	

	
private:
	monster_info info;
};

#endif // !__monsters__

