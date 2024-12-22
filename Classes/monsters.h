#pragma once

#ifndef __MONSTERS__
#define __MONSTERS__

#include "cocos2d.h"

#include "Monster_info.h"
#include "GameMenu.h"

using namespace std;

USING_NS_CC;

#define MONS_NUM 10     //�������� / ��
#define MAX_WAVE 3

class Monster : public Target
{
public:
	// ��������
	static Monster* create_Monster(monf type, const Vec2* path, const int& top);
	// ��ʼ��
	virtual bool init();
	// ��������
	virtual int get_type()const { return MONSTER_TARGET; }
	// ����Ѫ��
	void create_slider();
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
	int mons_tag;	//�����ǩ

	// ���ù�������
	void setType(monf type) { info = type; }
};




#endif // !__MONSTERS__

