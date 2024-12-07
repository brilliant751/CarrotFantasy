#pragma once

#ifndef __MONSTERS__
#define __MONSTERS__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


struct monster_info {
	int type;                                     //��¼��������
	int hp;                                       //��¼����Ѫ��
	int speed;                                    //��¼�����ƶ��ٶ�
	int rewards;                                  //Я���ܲ���
	int damage;                                   //���ܲ���ɵ��˺�
	int count;                                    //�߹��ĸ�����
};



class Monsters : public cocos2d::Sprite
{
public:
	static Sprite* create_Sprite();
	virtual bool init();

	void setType(int type);

	

	CREATE_FUNC(Monsters);
	
private:
	monster_info info;
};

#endif // !__MONSTERS__

