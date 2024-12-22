#pragma once

#ifndef __TOWERS_INFO__
#define __TOWERS_INFO__
using namespace std;

#define g_l 95



struct tower_info {
	int speed[3];//�����ӵ��ļ�� 
	int attack[3];//�����˺�
	float slow_down[3];//���ٰٷֱ�
	float duration[3];//���ٳ���ʱ��
	float radius[3];//�����뾶

	int cost[3];//����level����Ҫ��money
	int sell[3];//�����ɵõ�money
	/* ������Ⱦ���� */
	string D[3];
	string origin_url[3];
	string bullet_url[3];
	string atk_url[3][2];
	string effect_url[3];
	//sprite range scale ��ʱ����Ҫ��
	float scale[3];
};

const tower_info bottle{
	{0.5,0.35,0.25},{70,80,90},{0,0,0},{0,0,0},{1.768 * g_l,2.121 * g_l,2.652 * g_l},
	{100,180,260},{80,224,432},
	{"bottle_D1.png","bottle_D1.png","bottle_D1.png"},
	{"bottle_origin1.png","bottle_origin2.png","bottle_origin3.png"},
	{"bottle_bullet1.png","bottle_bullet2.png","bottle_bullet3.png"},
	{{"bottle_atk1_1.png","bottle_atk1_2.png"},{"bottle_atk2_1.png","bottle_atk2_2.png"},{"bottle_atk3_1.png","bottle_atk3_2.png"},},
	{"bottle_effect.png","bottle_effect.png","bottle_effect.png"},
	{1.7,2.2,2.7}
};

const tower_info shit{
	{1.5,1.2,1},{10,30,50},{0.4,0.55,0.7},{4,5,6},{1.414 * g_l,1.768 * g_l,1.768 * g_l},
	{120,220,260},{96,272,480},
	{"shit_D1.png","shit_D2.png","shit_D3.png"},
	{"shit_origin1.png","shit_origin2.png","shit_origin3.png"},
	{"shit_bullet1.png","shit_bullet2.png","shit_bullet3.png"},
	{{"shit_atk1_1.png","shit_atk1_2.png"},{"shit_atk2_1.png","shit_atk2_2.png"},{"shit_atk3_1.png","shit_atk3_2.png"},},
	{"shit_effect1.png","shit_effect2.png","shit_effect3.png"},
	{1.5,1.8,1.9}
};

const tower_info fan{
	{1.5,1.2,1},{80,150,200},{0,0,0},{0,0,0},{2.121 * g_l,2.652 * g_l,3.005 * g_l},
	{160,220,260},{128,304,512},
	{"fan_D1.png","fan_D2.png","fan_D3.png"},
	{"fan_origin1.png","fan_origin2.png","fan_origin3.png"},
	{"fan_bullet1.png","fan_bullet2.png","fan_bullet3.png"},
	{{"fan_atk1_1.png","fan_atk1_2.png"},{"fan_atk2_1.png","fan_atk2_2.png"},{"fan_atk3_1.png","fan_atk3_2.png"},},
	{"fan_effect1.png","fan_effect2.png","fan_effect2.png"},
	{2.2,2.7,3.2}
};

const tower_info towers[3]{
	bottle,shit,fan
};

#endif // !__TOWERS_INFO__
