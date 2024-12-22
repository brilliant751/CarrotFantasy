#pragma once

#ifndef __MAP_CHOOSE__
#define __MAP_CHOOSE__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace ui;

USING_NS_CC;

struct each_map {
	string map_url;      //地图在图集中的名字
	string waves_url;	 //waves在图集中的名字
	string towers_url;	     //可用防御塔在图集中的名字
	int stars = 0;		 //通关获得的星数
	bool all_clear = 0;  //
};

class MapChoose : public Scene
{
public:
	static Scene* create_Scene();
	void right_onButtonClicked(Ref* sender);
	void left_onButtonClicked(Ref* sender);
	void help_onButtonClicked(Ref* sender);
	void back_onButtonClicked(Ref* sender);
	void start_onButtonClicked(Ref* sender);
	virtual bool init();

	CREATE_FUNC(MapChoose);
private:
	Sprite* cur_map;
	Sprite* towers;
	Sprite* waves;
	Sprite* map_lock;
	Sprite* sp_stars;
	Sprite* sp_all_clear;
	Button* btn_start;
	void update_state(float dt);
	int level = 0;
	
	string all_clear_url = "all_clear.png";
};

#endif // !__MAP_CHOOSE__

