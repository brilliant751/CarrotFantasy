#pragma once

#ifndef __Help_Scene_1__
#define __Help_Scene_1__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


class HelpScene_1 : public Scene
{
public:
	static Scene* create_Scene();
	virtual bool init();

	void right_onButtonClicked(Ref* sender);
	void left_onButtonClicked(Ref* sender);
	void home_onButtonClicked(Ref* sender);

	CREATE_FUNC(HelpScene_1);
private:
	int page = 1;		//Ò³Âë±êÊ¶
	Sprite* picture;	//Í¼Æ¬
	Sprite* caption;	//×ÖÄ»
	Sprite* page_left;	//Ò³Âë
	/* url¿Õ¼ä */
	const string picture_url[5] = { "", "help_1.png", "help_2.png", "help_3.png", "help_4.png" };
	const string caption_url[5] = { "", "help_1_caption.png", "help_2_caption.png", "help_3_caption.png", "help_4_caption.png" };
	const string num_url[5] = { "num_middle.png", "num_1.png", "num_2.png", "num_3.png", "num_4.png" };
};

#endif // !__Help_Scene_1__

