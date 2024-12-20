#pragma once

#ifndef __MONSTERS__
#define __MONSTERS__

#include "cocos2d.h"

#include "Monster_info.h"
#include "GameMenu.h"

using namespace std;

USING_NS_CC;

extern int speed;
extern bool is_stop;
extern clock_t timer;

class Monster : public Target
{
public:
	// ��������
	static Monster* create_Monster(monf type);
	// ��ʼ��
	virtual bool init();
	// ��д���º���
	void update(float dt) override;
	// ����·��
	void set_route(const Vec2* path, const int& top) { route = path; this->top = top; }
	// ����create
	CREATE_FUNC(Monster);
	
private:
	monf info;	//��������

	/* ����·�߲��� */
	const Vec2* route;	//·������ָ��
	int rt = 1;		//ջ��ָ��
	int top;		//ջ��λ��

	// ���ù�������
	void setType(monf type) { info = type; }
};



#endif // !__MONSTERS__

