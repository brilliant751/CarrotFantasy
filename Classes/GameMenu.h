#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"
using namespace std;

USING_NS_CC;

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
#endif // !__GAME_MENU__