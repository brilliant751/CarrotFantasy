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
	{ 80, 2.5, 14, 1, 0 },
	{ 90, 2.7, 14, 1, 0 },
	{ 100, 2.9, 14, 1, 0 }
};
// ���й�
const monf flyers[2] = {
	{ 100, 5, 14, 1, 0 },
	{ 100, 5, 14, 1, 0 },
};
// �޹�
const monf bosses[3] = {
	{ 2000, 2, 168, 2, 0 },
	{ 3000, 2, 168, 2, 0 },
	{ 5000, 2, 168, 2, 0 }
};

#endif // !__MONSTER_INFO__
