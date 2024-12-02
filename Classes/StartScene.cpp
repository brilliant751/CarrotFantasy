
#include "StartScene.h"
#include "EnterScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;



Scene* StartScene::create_Scene()
{
	return StartScene::create();
}

static void enterCall(Ref* eSender)
{
    auto next = Enter::create_Scene();
    Director::getInstance()->replaceScene(next);
}

/* ����ļ��޷��򿪣���ӡ������Ϣ */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//static Sprite* sp_create(const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0, Scene* it)
//{
//    Sprite* newsp = Sprite::create();
//}

/* ��ʼ������ */
bool StartScene::init()
{
    // ��ʹ�û���ĳ�ʼ������
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1960,1080)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /************     ����     ************/

    constexpr int btnY = 180;           //��ť�߶�
    constexpr float btn_scale = 1.1f;   //��ť�Ŵ���
    constexpr float map_scale = 1.5f;   //��ͼ�Ŵ���
    const Vec2 bg(visibleSize / 2);     //��ͼλ��
    const Vec2 crt(980, 600);           //�ܲ�λ��
    const Vec2 lf1(900, 715);           //Ҷ��1
    const Vec2 lf2(990, 745);           //Ҷ��2
    const Vec2 lf3(1080, 715);          //Ҷ��3
    const Vec2 tm(960, 450);            //�̱�λ��
    const Vec2 ad_btn(600, btnY);       //ð��ģʽ
    const Vec2 boss_btn(970, btnY);     //bossģʽ
    const Vec2 nest_btn(1340, btnY);    //������


    /**************************************/

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("StartScene/StartScene.plist");

    /* ��������ıհ����� */
    //lambda���ʽ
    //pctname��  ͼ���е�����
    //pos��      ����
    //scale��    �Ŵ���
    //layer��    ���ò���
    auto sp_create = [&](const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0) {
        Sprite* newsp = Sprite::create();
        newsp->initWithSpriteFrameName(pctname);
        newsp->setPosition(pos);
        newsp->setScale(scale);
        this->addChild(newsp, layer);
        return newsp;
        };

    /* ���� ð��ģʽ ��ť */
    auto advenBtn = Button::create(
        "StartScene/contents/btn_adventure_normal.png",
        "StartScene/contents/btn_adventure_pressed.png",
        "StartScene/contents/btn_adventure_normal.png");
    advenBtn->setPosition(ad_btn);
    advenBtn->setScale(btn_scale);

    advenBtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                enterCall(this);
                break;
            default:
                break;
        }
        });

    addChild(advenBtn);

    /* ���� bossģʽ ��ť */
    auto bossBtn = Button::create(
        "StartScene/contents/btn_boss_normal.png",
        "StartScene/contents/btn_boss_pressed.png",
        "StartScene/contents/btn_boss_normal.png");

    bossBtn->setPosition(boss_btn);
    bossBtn->setScale(btn_scale);
    addChild(bossBtn);

    /* ���� ������ ��ť */
    auto nestBtn = Button::create(
        "StartScene/contents/btn_nest_normal.png",
        "StartScene/contents/btn_nest_pressed.png",
        "StartScene/contents/btn_nest_normal.png");

    nestBtn->setPosition(nest_btn);
    nestBtn->setScale(btn_scale);
    addChild(nestBtn);

    /* �������� */
    auto mainbg = sp_create("mainbg.png", bg, map_scale, -1);

    /* �����ܲ� */
    auto carrot = sp_create("carrot.png", crt, map_scale, 3);
    
    /* ��������Ҷ�� */
    auto leaf1 = sp_create("leaf-1.png", lf1, map_scale, 1);
    auto leaf2 = sp_create("leaf-2.png", lf2, map_scale, 2);
    auto leaf3 = sp_create("leaf-3.png", lf3, map_scale, 1);

    /* �����̱� */
    auto gameTM = sp_create("gameTM.png", tm, map_scale, 4);


    return true;
}

/* �رս��棬�˳����� */
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

