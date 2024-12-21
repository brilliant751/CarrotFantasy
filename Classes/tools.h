#pragma once

#include "cocos2d.h"
#include "GameMenu.h"
#include "ui/cocosGUI.h"

USING_NS_CC;
using namespace std;
using namespace ui;

/************ ���ߺ��� ************/
const Vec2 origin = Vec2(240, 100); //��ͼ�������
Vec2 get_po(int line, int row);		//��ȡ�������ĵ�����
int get_line(float y);				//��ȡ���ӵ���
int get_row(float x);				//��ȡ���ӵ���
int get_tag_waves(int tag);			//��ȡ��Ӧ����
void update_tag(int& tag, int waves);	//����tag
float cal_distance(const Vec2& po1, const Vec2& po2);
float cal_relative_angle(const Vec2& po1, const Vec2& po2);
Vec2 pos_check(const Vec2& ex, const Vec2& cur);
void update_pos(Vec2& pos, const Vec2& ex, const Vec2& cur);


/************ �������� ************/
// ��������
Sprite* sp_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0);
// ������ǩ
Label* lb_create(Scene* parent, const string text, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0);
Label* lb_create(Scene* parent, const int num, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0);
// ������ť
Button* btn_create(Scene* parent, const string& normal, const string& pressed, const Vec2& pos, const float& scale = 1.0f, int layer = 1);
Button* btn_create(Layer* parent, const string& normal, const string& pressed, const Vec2& pos, const float& scale = 1.0f, int layer = 1);

// �����ɹ�������
Target* targ_create(Scene* parent, const string& pctname, const Vec2& pos, const float& scale = 1.5f, int layer = 0);


