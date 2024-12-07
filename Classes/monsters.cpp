
#include "monsters.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace ui;
using namespace std;

/* 创建怪物 */
Sprite* Monsters::create_Sprite()
{
	return Monsters::create();
}

/* 怪物初始化 */
bool Monsters::init()
{
	if (!Sprite::init())
		return false;





	return true;
}