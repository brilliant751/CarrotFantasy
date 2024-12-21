#pragma once

#ifndef __SKYLINE_01__
#define __SKYLINE_01__

#include "cocos2d.h"
#include "tools.h"
#include "Monsters.h"

USING_NS_CC;
using namespace std;

/* ������ */
class Map_1_01 : public Scene
{
	friend void update_tag(int& tag, int waves);
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(Map_1_01);

	// ����������
	void create_tower(int type,Vec2 po,int line,int row);

	// ���²���
	void update_waves();

	// ��ȡ�ϰ�������
	int get_n_barrier() { return n_barrier; };

	// ��ʱˢ���ຯ��
	void create_monster(float dt);	//��������
	void update_create(float dt);	//ˢ�½��찴ť
	void update_money(float dt);    //ˢ�½��Monster** get_monsters(float dt);
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
	const int total_waves = 15;		//�ܲ���
	int c_hp = 10;			//�ܲ�����ֵ
	bool is_pause = 0;		//�Ƿ���ͣ
	int money = 5000;		//��Ǯ
	int n_barrier = 8;		//�ϰ�������
	int cur_line;
	int cur_row;
	int tag1_1;		//ѡ������TAG
	int tag1_2;		//  ѡ��ʵ��tag
	Vec2 cur_pos;
	int map_clicked_1 = 0;//״̬ 0 ֮ǰ��δ��� 1 ֮ǰ�Ѿ������һ���ɽ����λ�� 2 ֮ǰ�Ѿ������һ��������


	/* ����������� */
	float mons_scale = 1.5f;
	string mons_url[16] = { "", 
		"Monster01_0.png", "Monster02_0.png", "Monster02_0.png", 
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png", 
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png", 
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png",
		"Monster02_0.png", "Monster02_0.png", "Monster02_0.png" };
	//    XX     XX      XX
	// �ؿ���� ���� �ڼ�������
	int mons_tag = 10101;
	int least = 10101;

};

#endif //!__SKYLINE_01__