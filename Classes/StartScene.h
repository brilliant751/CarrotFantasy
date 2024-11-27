#pragma once

#ifndef __START_SCENE_MENU__
#define __START_SCENE_MENU__

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

	// �رճ���
	void menuCloseCallback(Ref* pSender);


	CREATE_FUNC(StartScene);

};

#endif