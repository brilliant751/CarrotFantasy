
#include "monsters.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace ui;
using namespace std;

/* �������� */
Sprite* Monsters::create_Sprite()
{
	return Monsters::create();
}

/* �����ʼ�� */
bool Monsters::init()
{
	if (!Sprite::init())
		return false;





	return true;
}