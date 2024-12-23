#pragma once

#ifndef __SKYLINE_02__
#define __SKYLINE_02__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/* 主场景 */
class Map_1_02 : public Scene
{
public:
	// 创建一个场景
	static Scene* create_Scene();

	// 初始化
	virtual bool init();

	// 更新波次
	void update_waves();

	// 获取障碍物数量
	int get_n_barrier() { return n_barrier; };

	// 定时刷新类函数
	void create_monster(float dt);	//创建怪物

	// 定义create
	CREATE_FUNC(Map_1_02);

	void update_create(float dt);	//刷新建造按钮
	void update_money(float dt);    //刷新金币Monster** get_monsters(float dt);
	int occupy_2[8][12] = {
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	0,2,2,0,0,0,0,0,0,0,0,0,
	0,2,2,0,1,1,1,1,1,1,2,0,
	0,0,0,0,2,0,2,0,2,1,2,2,
	0,0,1,1,1,1,1,1,1,1,2,2,
	2,2,1,2,0,2,0,0,2,2,0,0,
	0,0,1,1,1,1,1,1,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,1,1
	};
private:
	//int speed = 1;
	const int total_waves = 20;		//总波次
	int c_hp = 10;			//萝卜生命值
	int n_barrier = 8;		//障碍物数量
	int cur_line;
	int cur_row;
	int map_clicked_2 = 0;//状态 0 之前还未点击 1 之前已经点击了一个可建造的位置 2 之前已经点击了一个防御塔
	int tag2_1;//选中虚线TAG
	int tag2_2;//  选择实线tag
	Vec2 cur_pos;

	/* 创建怪物参数 */
	float mons_scale = 1.5f;
	string mons_url[16] = { "",
		"Monster01_0.png", "Monster02_0.png", "Monster04_0.png",
		"Monster05_0.png", "Monster06_0.png", "Monster05_0.png",
		"Monster02_0.png", "Monster01_0.png", "Monster06_0.png",
		"Monster05_0.png", "Monster01_0.png", "Monster02_0.png",
		"Monster02_0.png", "Monster06_0.png", "Monster04_0.png" };
	//    XX     XX      XX
	// 关卡序号 波次 第几个怪物
	int mons_tag = 10101;
	int least = 10101;
};

#endif //!__SKYLINE_02__