#pragma once

#ifndef __SKYLINE_02__
#define __SKYLINE_02__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/* ������ */
class Map_1_02 : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

	// ���²���
	void update_waves();

	// ��ȡ�ϰ�������
	int get_n_barrier() { return n_barrier; };

	// ��ʱˢ���ຯ��
	void create_monster(float dt);	//��������

	// ����create
	CREATE_FUNC(Map_1_02);

	void update_create(float dt);	//ˢ�½��찴ť
	void update_money(float dt);    //ˢ�½��Monster** get_monsters(float dt);
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
	const int total_waves = 20;		//�ܲ���
	int c_hp = 10;			//�ܲ�����ֵ
	int n_barrier = 8;		//�ϰ�������
	int cur_line;
	int cur_row;
	int map_clicked_2 = 0;//״̬ 0 ֮ǰ��δ��� 1 ֮ǰ�Ѿ������һ���ɽ����λ�� 2 ֮ǰ�Ѿ������һ��������
	int tag2_1;//ѡ������TAG
	int tag2_2;//  ѡ��ʵ��tag
	Vec2 cur_pos;

	/* ����������� */
	float mons_scale = 1.5f;
	string mons_url[16] = { "",
		"Monster01_0.png", "Monster02_0.png", "Monster04_0.png",
		"Monster05_0.png", "Monster06_0.png", "Monster05_0.png",
		"Monster02_0.png", "Monster01_0.png", "Monster06_0.png",
		"Monster05_0.png", "Monster01_0.png", "Monster02_0.png",
		"Monster02_0.png", "Monster06_0.png", "Monster04_0.png" };
	//    XX     XX      XX
	// �ؿ���� ���� �ڼ�������
	int mons_tag = 10101;
	int least = 10101;
};

#endif //!__SKYLINE_02__