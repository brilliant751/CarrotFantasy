#pragma once

#ifndef __MAP_CHOOSE__
#define __MAP_CHOOSE__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace ui;

USING_NS_CC;

struct each_map {
	string map_url;      //��ͼ��ͼ���е�����
	string waves_url;	 //waves��ͼ���е�����
	string towers_url;	     //���÷�������ͼ���е�����
	int stars = 0;		 //ͨ�ػ�õ�����
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

