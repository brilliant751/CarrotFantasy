
#include "StartScene.h"
#include "EnterScene.h"
#include "HelpScene_1.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* �������� */
Scene* StartScene::create_Scene()
{
	return StartScene::create();
}

/* �����½�ѡ�� */
static void enterCall(Ref* eSender)
{
    auto next = Enter::create_Scene();
    Director::getInstance()->replaceScene(next);
}

/* ������� */
static void helpCall(Ref* eSender)
{
    auto next = HelpScene_1::create_Scene();
    Director::getInstance()->replaceScene(next);
}

/* ����ļ��޷��򿪣���ӡ������Ϣ */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* ��ʼ������ */
bool StartScene::init()
{
    // ��ʹ�û���ĳ�ʼ������
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1960,1080)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Ԥ���ؾ���ͼ��
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

    /* ������ť�ıհ����� */
    //lambda���ʽ
    //normal��   ����״̬��ʾ
    //pressed��  ���״̬��ʾ
    //pos��      ����
    //scale��    �Ŵ���
    //layer��    ���ò���
    auto btn_create = [&](const string& normal, const string& pressed,
        const Vec2& pos, const float& scale = 1.0f, int layer = 1)
        {
            auto btn = Button::create();
            btn->loadTextures(normal, pressed, normal);
            btn->setPosition(pos);
            btn->setScale(scale);
            this->addChild(btn, layer);
            return btn;
        };

    /************     ����     ************/

    constexpr int btnY1 = 180;              //��ť�߶�
    constexpr int btnY2 = 400;              //С��ť�߶�
    constexpr float btn_scale = 1.1f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;       //��ͼ�Ŵ���
    const Vec2 bg(visibleSize / 2);         //��ͼλ��
    const Vec2 crt(980, 600);               //�ܲ�λ��
    const Vec2 lf1(900, 715);               //Ҷ��1
    const Vec2 lf2(990, 745);               //Ҷ��2
    const Vec2 lf3(1080, 715);              //Ҷ��3
    const Vec2 tm(960, 450);                //�̱�λ��
    const Vec2 ad_btn(600, btnY1);          //ð��ģʽ
    const Vec2 boss_btn(970, btnY1);        //bossģʽ
    const Vec2 nest_btn(1340, btnY1);       //������
    const Vec2 setting_btn(560, btnY2);     //���ð�ť
    const Vec2 help_btn(1380, btnY2);       //������ť

    /**************************************/

    /* ���� ð��ģʽ ��ť */
    auto adventure = btn_create(
        "StartScene/btn/btn_adventure_normal.png",
        "StartScene/btn/btn_adventure_pressed.png",
        ad_btn, btn_scale);
    // �л�����
    adventure->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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

    /* ���� ���� ��ť */
    auto settings = btn_create(
        "StartScene/btn/btn_setting_normal.png",
        "StartScene/btn/btn_setting_pressed.png",
        setting_btn, btn_scale, 1);

    /* ���� ���� ��ť */
    auto help = btn_create(
        "StartScene/btn/btn_help_normal.png",
        "StartScene/btn/btn_help_pressed.png",
        help_btn, btn_scale, 1);
    // �л�����
    help->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                helpCall(this);
                break;
            default:
                break;
        }
        });

    /* ���� bossģʽ ��ť */
    auto boss = sp_create("btn_boss_normal.png", boss_btn, btn_scale, 1);

    /* ���� ������ ��ť */
    auto nest = sp_create("btn_nest_normal.png", nest_btn, btn_scale, 1);

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

