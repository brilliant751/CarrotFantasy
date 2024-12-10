#pragma once

#ifndef __MAP_CHOOSE__
#define __MAP_CHOOSE__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

struct each_map {
	string map_url;      //��ͼ��ͼ���е�����
	string waves_url;	 //waves��ͼ���е�����
	string towers_url;	     //���÷�������ͼ���е�����
	int stars = 0;		 //ͨ�ػ�õ�����
	bool all_clear = 0;	 //�Ƿ�all clear
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
	int level = 0;
	each_map all_map[3] = {
	{"level_1.png","total_15_waves.png","towers_1.png"},
	{"level_2.png","total_20_waves.png","towers_2.png"},
	{"level_3.png","total_20_waves.png","towers_3.png"}
	};
	string stars_url[3] = { "stars_1.png","stars_2.png" ,"stars_3.png" };//stars��Ӧstars_url[stars-1]
	string all_clear_url = "all_clear.png";
};

#endif // !__MAP_CHOOSE__

