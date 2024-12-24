#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"
#include "ui/cocosGUI.h"
//#include "monsters.h"

USING_NS_CC;
using namespace ui;
using namespace std;

#define BARRIER_TARGET 0
#define MONSTER_TARGET 1

class Monster;

/* �����˵� */
class PauseMenu : public Layer
{
public:
	// ����һ����
	static Layer* create_Layer();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(PauseMenu);
};


/* ����ʱ */
class CountDown : public Layer {
public:
	// ����һ����
	static Layer* create_Layer();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(CountDown);
private:
	Sprite* count;
	string count_url[3] = {
		"start_time_1.png","start_time_2.png","start_time_3.png"
	};
	int co = 2;


};

/* �ɹ������� */
class Target : public Sprite
{
public:
	double hp;		//Ѫ��
	double max_hp;	//���Ѫ��
	int reward = 200;		//������
	Sprite* selected;		//������ʶ
	Sprite* hp_holder;		//Ѫ����
	LoadingBar* hp_slider;	//Ѫ��

	// ����Ѫ��
	void setHP(int max_hp) { this->max_hp = hp = max_hp; }
	// ��ȡ����
	virtual int get_type()const { return BARRIER_TARGET; }
	// ����Ѫ��
	virtual void create_slider();
	// �ܵ��˺�
	virtual void get_hurt(int damage);

	// ��ȡ������ʶ
	Sprite* get_selected_sprite()const { return selected; }
	// ����create
	CREATE_FUNC(Target);
};




#endif // !__GAME_MENU__