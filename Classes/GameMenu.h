#pragma once

#ifndef __GAME_MENU__
#define __GAME_MENU__

#include "cocos2d.h"

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

#endif // !__GAME_MENU__