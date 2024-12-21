#pragma once

#include "cocos2d.h"
#include "GameMenu.h"
#include "ui/cocosGUI.h"

USING_NS_CC;
using namespace std;
using namespace ui;

/************ 工具函数 ************/
const Vec2 origin = Vec2(240, 100); //地图坐标起点
Vec2 get_po(int line, int row);		//获取格子中心点坐标
int get_line(float y);				//获取格子的行
int get_row(float x);				//获取格子的列
int get_tag_waves(int tag);			//获取对应波次
void update_tag(int& tag, int waves);	//更新tag
float cal_distance(const Vec2& po1, const Vec2& po2);
float cal_relative_angle(const Vec2& po1, const Vec2& po2);
Vec2 pos_check(const Vec2& ex, const Vec2& cur);
void update_pos(Vec2& pos, const Vec2& ex, const Vec2& cur);


/************ 创建对象 ************/
// 创建精灵
Sprite* sp_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0);
// 创建标签
Label* lb_create(Scene* parent, const string text, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0);
Label* lb_create(Scene* parent, const int num, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0);
// 创建按钮
Button* btn_create(Scene* parent, const string& normal, const string& pressed, const Vec2& pos, const float& scale = 1.0f, int layer = 1);
Button* btn_create(Layer* parent, const string& normal, const string& pressed, const Vec2& pos, const float& scale = 1.0f, int layer = 1);

// 创建可攻击对象
Target* targ_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.5f, int layer = 0);


