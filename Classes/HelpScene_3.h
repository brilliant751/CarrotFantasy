#pragma once

#ifndef __Help_Scene_3__
#define __Help_Scene_3__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


class HelpScene_3 : public Scene
{
public:
	static Scene* create_Scene();
	virtual bool init();

	void right_onButtonClicked(Ref* sender);
	void left_onButtonClicked(Ref* sender);
	void back_onButtonClicked(Ref* sender);

	CREATE_FUNC(HelpScene_3);
private:
	int page = 1;		//页码标识
	Sprite* picture;	//图案
	Sprite* page_left;	//页码
	/* url空间 */
	string picture_url[11] = { "", "tower_1.png","tower_2.png", "tower_3.png", "tower_4.png",
	"tower_5.png","tower_6.png", "tower_7.png", "tower_8.png","tower_9.png", "tower_10.png", 
	};//对应[page-1]
	string num_url[11] = { "num_middle.png","num_1.png","num_2.png","num_3.png","num_4.png",
		"num_5.png","num_6.png","num_7.png","num_8.png","num_9.png","num_10.png"
	};
};

#endif // !__Help_Scene_3__

