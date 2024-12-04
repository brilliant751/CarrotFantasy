#pragma once

#ifndef __MAP_CHOOSE__
#define __MAP_CHOOSE__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

struct each_map {
	string map_url;      //地图在图集中的名字
	string waves_url;	 //waves在图集中的名字
	string towers[3];	 //可用防御塔在图集中的名字
	int stars = 0;		 //通关获得的星数
	bool all_clear = 0;	 //是否all clear
};



class MapChoose : public Scene
{
public:
	static Scene* create_Scene();
	void right_onButtonClicked(Ref* sender);
	void left_onButtonClicked(Ref* sender);
	virtual bool init();

	CREATE_FUNC(MapChoose)
private:
	Sprite* cur_map;
	int level = 0;
	each_map all_map[3] = {
	{"level_1.png","total_15_waves.png",{"tower_1.png","tower_2.png"," "}},
	{"level_2.png","total_20_waves.png",{"tower_1.png","tower_2.png","tower_3.png"}},
	{"level_3.png","total_20_waves.png",{"tower_1.png","tower_2.png","tower_4.png"}}
	};
	string stars_url[3] = { "stars_1.png","stars_2.png" ,"stars_3.png" };//stars对应stars_url[stars-1]
	string all_clear_url = "all_clear.png";
};

#endif // !__MAP_CHOOSE__

