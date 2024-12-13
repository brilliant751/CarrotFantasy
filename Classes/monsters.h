#pragma once

#ifndef __MONSTERS__
#define __MONSTERS__

#include "cocos2d.h"

#include "Monster_info.h"

using namespace std;

USING_NS_CC;

class Monster : public cocos2d::Sprite
{
public:
	// ��������
	static Monster* create_Monster(monf type);
	// ��ʼ��
	virtual bool init();
	// ��д���º���
	void update(float dt) override;
	// ����create
	CREATE_FUNC(Monster);
	
private:
	monf info;	//��������
	// ���ù�������
	void setType(monf type) { info = type; }
};

#endif // !__MONSTERS__

