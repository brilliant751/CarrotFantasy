#pragma once

#ifndef __MONSTER_INFO__
#define __MONSTER_INFO__

/* 怪物类型宏 */
#define PUPIL_1 pupils[0]
#define PUPIL_2 pupils[1]
#define PUPIL_3 pupils[2]
#define FLYER_1 flyers[0]
#define FLYER_2 flyers[1]
#define BOSS_1 bosses[0]
#define BOSS_2 bosses[1]
#define BOSS_3 bosses[2]

// 怪物属性
typedef struct monster_info {
	int hp;                                       //记录怪物血量
	int speed;                                    //记录怪物移动速度
	int rewards;                                  //携带萝卜币
	int damage;                                   //对萝卜造成的伤害
	int count;                                    //走过的格子数
	//string url[2];
}monf;

/* 存储怪物类型 */
// 小喽啰
const monf pupils[3] = {
	{ 80, 2.5, 14, 1, 0 },
	{ 90, 2.7, 14, 1, 0 },
	{ 100, 2.9, 14, 1, 0 }
};
// 飞行怪
const monf flyers[2] = {
	{ 100, 5, 14, 1, 0 },
	{ 100, 5, 14, 1, 0 },
};
// 巨怪
const monf bosses[3] = {
	{ 2000, 2, 168, 2, 0 },
	{ 3000, 2, 168, 2, 0 },
	{ 5000, 2, 168, 2, 0 }
};

#endif // !__MONSTER_INFO__
