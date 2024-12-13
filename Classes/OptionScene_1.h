#pragma once

#ifndef __Option_Scene_1__
#define __Option_Scene_1__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class OptionScene_1 : public Scene
{
public:
	// ����һ������
	static Scene* create_Scene();

	// ��ʼ��
	virtual bool init();

	void back_onButtonClicked(Ref* sender);
	void reset_onButtonClicked(Ref* sender);

	CREATE_FUNC(OptionScene_1);

};
/* ����ȷ�ϵ��� */
class PopReset : public Layer
{
public:
	// ����һ����
	static Layer* create_Layer();

	// ��ʼ��
	virtual bool init();

	// ����create
	CREATE_FUNC(PopReset);
};

#endif