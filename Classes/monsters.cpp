
#include "monsters.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace ui;
using namespace std;

/* �������� */
Monster* Monster::create_Monster(monf type)
{
	auto mt = Monster::create();
	mt->setType(type);
	return mt;
}

/* �����ʼ�� */
bool Monster::init()
{
	if (!Sprite::init())
		return false;





	return true;
}