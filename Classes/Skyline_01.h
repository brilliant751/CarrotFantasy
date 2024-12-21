#pragma once

#ifndef __SKYLINE_01__
#define __SKYLINE_01__

#include "cocos2d.h"
#include "tools.h"
#include "Monsters.h"

USING_NS_CC;
using namespace std;

/* 主场景 */
class Map_1_01 : public Scene
{
	friend void update_tag(int& tag, int waves);
public:
	// 创建一个场景
	static Scene* create_Scene();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(Map_1_01);

	// 创建防御塔
	void create_tower(int type,Vec2 po,int line,int row);

	// 更新波次
	void update_waves();

	// 获取障碍物数量
	int get_n_barrier() { return n_barrier; };

	// 定时刷新类函数
	void create_monster(float dt);	//创建怪物
	void update_create(float dt);	//刷新建造按钮
	void update_money(float dt);    //刷新金币Monster** get_monsters(float dt);
	//int get_mons_tag() { return mons_tag; };
	//int get_waves() { return waves; };
	int occupy_1[8][12] = {
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	0,0,0,2,2,2,2,2,2,0,0,0,
	0,1,0,2,2,2,2,2,2,0,1,1,
	0,1,0,0,2,0,0,2,0,0,1,0,
	0,1,2,0,1,1,1,1,0,2,1,0,
	0,1,1,1,1,2,2,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,0,0,1,1
	};
private:
	const int total_waves = 15;		//总波次
	int c_hp = 10;			//萝卜生命值
	bool is_pause = 0;		//是否暂停
	int money = 5000;		//金钱
	int n_barrier = 8;		//障碍物数量
	int cur_line;
	int cur_row;
	int tag1_1;		//选中虚线TAG
	int tag1_2;		//  选择实线tag
	Vec2 cur_pos;
	int map_clicked_1 = 0;//状态 0 之前还未点击 1 之前已经点击了一个可建造的位置 2 之前已经点击了一个防御塔


	/* 创建怪物参数 */
	float mons_scale = 1.5f;
	string mons_url[16] = { "", 
		"Monster01_0.png", "Monster02_0.png", "Monster02_0.png", 
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png", 
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png", 
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png",
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png" };
	//    XX     XX      XX
	// 关卡序号 波次 第几个怪物
	int mons_tag = 10101;
	int least = 10101;

};

#endif //!__SKYLINE_01__