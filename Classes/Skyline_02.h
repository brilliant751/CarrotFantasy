#pragma once

#ifndef __SKYLINE_02__
#define __SKYLINE_02__

#include "cocos2d.h"

USING_NS_CC;

/* ������ */
class Map_1_02 : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

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
	bool is_pause = 0;		//�Ƿ���ͣ
	int money = 5000;		//��Ǯ
	int waves = 1;			//����
	int cur_line;
	int cur_row;
	int map_clicked_2 = 0;//״̬ 0 ֮ǰ��δ��� 1 ֮ǰ�Ѿ������һ���ɽ����λ�� 2 ֮ǰ�Ѿ������һ��������
	int tag2_1;//ѡ������TAG
	int tag2_2;//  ѡ��ʵ��tag
	Vec2 cur_pos;
};

#endif //!__SKYLINE_02__