#pragma once

#ifndef __MONSTER_INFO__
#define __MONSTER_INFO__

/* �������ͺ� */
#define PUPIL_1 pupils[0]
#define PUPIL_2 pupils[1]
#define PUPIL_3 pupils[2]
#define FLYER_1 flyers[0]
#define FLYER_2 flyers[1]
#define BOSS_1 bosses[0]
#define BOSS_2 bosses[1]
#define BOSS_3 bosses[2]

// ��������
typedef struct monster_info {
	int hp;                                       //��¼����Ѫ��
	int speed;                                    //��¼�����ƶ��ٶ�
	int rewards;                                  //Я���ܲ���
	int damage;                                   //���ܲ���ɵ��˺�
	int count;                                    //�߹��ĸ�����
	//string url[2];
}monf;

/* �洢�������� */
// Сආ�
const monf pupils[3] = {
	{ 50, 2.5, 20, 1, 0 },
	{ 80, 2.5, 20, 1, 0 },
	{ 100, 2.5, 20, 1, 0 }
};
// ���й�
const monf flyers[2] = {
	{ 50, 5, 20, 1, 0 },
	{ 80, 5, 20, 1, 0 },
};
// �޹�
const monf bosses[3] = {
	{ 5000, 1, 200, 3, 0 },
	{ 10000, 1, 200, 3, 0 },
	{ 5000, 2, 200, 3, 0 }
};

#endif // !__MONSTER_INFO__
