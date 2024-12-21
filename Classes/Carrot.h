#pragma once

#ifndef _CARROT_
#define _CARROT_
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

//    const Vec2 crt(1250, origin.y + mapY[6]);              //萝卜位置
//const Vec2 po_chp_bg(1330, origin.y + mapY[6] - 10);   //萝卜血条底图位置
//const Vec2 po_chp_num(1343, origin.y + mapY[6] - 10);  //萝卜血条数字位置
class Carrot :public::cocos2d::Sprite {
private:
	int c_hp = 10;			//萝卜生命值
	Vec2 c_pos;//萝卜位置
	int map;
	string chp_url[10] = {
		"HP_1.PNG" ,"HP_2.PNG" ,"HP_3.PNG" ,"HP_4.PNG" ,"HP_5-6.PNG" ,
		"HP_5-6.PNG" ,"HP_7-8.PNG" ,"HP_7-8.PNG","HP_9.PNG","HP_MAX.PNG" };
	Sprite* chp_bg;//萝卜血条底图
	Label* chp_num;//萝卜血条数字
public:
	// 创建萝卜
	static Carrot* create_Carrot(const Vec2& carrot_pos, Scene* scene);
	// 初始化
	virtual bool init();

	// 设置位置
	void _setPosition(const Vec2& carrot_pos, const Vec2& chp_pos);

	void _setSpriteFrame(const string& chp_url);

	void _setScale(const float& carrot_scale, const float& chp_scale);

	void cut_chp();//萝卜掉血


	// 定义create
	CREATE_FUNC(Carrot);
};
class PopCarrot : public Layer
{
public:
	// 创建一个层
	static Layer* create_Layer();

	// 初始化
	virtual bool init();

	// 定义create
	CREATE_FUNC(PopCarrot);
};
#endif // !_CARROT_

