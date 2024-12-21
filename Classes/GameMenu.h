#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"
#include "ui/cocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;

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
	double hp;	//Ѫ��
	double max_hp;	//Ѫ��
	Sprite* selected;	//������ʶ
	Sprite* hp_holder;	//Ѫ����
	LoadingBar* hp_slider;	//Ѫ��

	CREATE_FUNC(Target);
	void setHP(int max_hp) { this->max_hp = hp = max_hp; }
	virtual void create_slider();
	virtual void get_hurt(int damage)
	{
		hp -= damage;
		float percent = hp / max_hp * 100;
		hp_slider->setPercent(percent);
	}

	// ��ȡ������ʶ
	Sprite* get_selected_sprite()const { return selected; }
};




#endif // !__GAME_MENU__