#pragma once

#ifndef _CARROT_
#define _CARROT_
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

//    const Vec2 crt(1250, origin.y + mapY[6]);              //�ܲ�λ��
//const Vec2 po_chp_bg(1330, origin.y + mapY[6] - 10);   //�ܲ�Ѫ����ͼλ��
//const Vec2 po_chp_num(1343, origin.y + mapY[6] - 10);  //�ܲ�Ѫ������λ��
class Carrot :public::cocos2d::Sprite {
private:
	int c_hp = 10;			//�ܲ�����ֵ
	Vec2 c_pos;//�ܲ�λ��
	int map;
	string chp_url[10] = {
		"HP_1.PNG" ,"HP_2.PNG" ,"HP_3.PNG" ,"HP_4.PNG" ,"HP_5-6.PNG" ,
		"HP_5-6.PNG" ,"HP_7-8.PNG" ,"HP_7-8.PNG","HP_9.PNG","HP_MAX.PNG" };
	Sprite* chp_bg;//�ܲ�Ѫ����ͼ
	Label* chp_num;//�ܲ�Ѫ������
public:
	// �����ܲ�
	static Carrot* create_Carrot(const Vec2& carrot_pos, Scene* scene);
	// ��ʼ��
	virtual bool init();

	// ����λ��
	void _setPosition(const Vec2& carrot_pos, const Vec2& chp_pos);

	void _setSpriteFrame(const string& chp_url);

	void _setScale(const float& carrot_scale, const float& chp_scale);

	void cut_chp();//�ܲ���Ѫ


	// ����create
	CREATE_FUNC(Carrot);
};
class PopCarrot : public Layer
{
public:
	// ����һ����
	static Layer* create_Layer();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(PopCarrot);
};
#endif // !_CARROT_

