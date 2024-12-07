#pragma once

#ifndef __monsters__
#define __monsters__

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
	static void create_Sprite();
	virtual bool init();


	

	CREATE_FUNC(Monsters);
	
private:
	monster_info info;
};

#endif // !__monsters__

