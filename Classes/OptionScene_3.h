#ifndef __Option_Scene_3__
#define __Option_Scene_3__

#include "cocos2d.h"

using namespace std;

USING_NS_CC;


class OptionScene_3 : public Scene
{
public:
	static Scene* create_Scene();
	virtual bool init();

	void back_onButtonClicked(Ref* sender);

	CREATE_FUNC(OptionScene_3);
private:

};

#endif // !__Option_Scene_3__