
#include "EnterScene.h"
#include "MapChoose.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* ����ļ��޷��򿪣���ӡ������Ϣ */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* MapChoose::create_Scene()
{
    return MapChoose::create();
}


bool MapChoose::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MapChoose/MapChoose.plist");

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
    //normal_name��   ����״̬��ͼ���е�����
    //pressed_name��  ѡ��״̬��ͼ���е�����
    //locked_name��   ���ɵ��״̬��ͼ���е����� 
    //pos��           ����
    //scale��         �Ŵ���
    //layer��         ���ò���
    //btn_type:       ��ť���
    //                         1 - back
    //                         2 - help
    //                         3 - start
    auto btn_create = [&](const string& normal_name, const string& pressed_name, const string& locked_name,
        const Vec2& pos, int btn_type, const float& scale = 1.1f, int layer = 0) {
            auto temp_btn = Button::create(normal_name, pressed_name, locked_name);
            temp_btn->setPosition(pos);
            temp_btn->setScale(scale);

            temp_btn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        switch (btn_type) {
                            case 1:
                                //�ص�EnterScene
                                break;
                            case 2:
                                //��HelpScene
                                break;
                            case 3:
                                //��ʼ��Ϸ
                                break;
                            default:
                                break;
                        };
                        break;
                    default:
                        break;
                }
                });
            addChild(temp_btn, layer);

            return temp_btn;

        };
    
    /************     ����     ************/

    const Vec2 po_bg(visibleSize / 2);     //��ͼλ��
    constexpr float btn_scale = 1.1f;      //��ť�Ŵ���
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 po_bg_left(495, 185);       //���±���λ��
    const Vec2 po_bg_right(1482, 183);     //���±���λ��
    const Vec2 po_btn_back(330, 953);      //���ذ�ťλ��
    const Vec2 po_btn_help(1628, 953);     //������ťλ��
    const Vec2 po_btn_start(980, 150);     //��ʼ��ťλ��

    /**************************************/

    /* �������� */
    auto bg = sp_create("bg.png", po_bg, map_scale, -1);
    auto bg_left = sp_create("bg_left.png", po_bg_left, map_scale, 0);
    auto bg_right = sp_create("bg_right.png", po_bg_right, map_scale, 0);

    /* ������ť */
    //����
    auto btn_back = btn_create(
        "MapChoose/contents/btn_back_normal.png",
        "MapChoose/contents/btn_back_pressed.png",
        "MapChoose/contents/btn_back_normal.png",
        po_btn_back, 1, 1.2);
    //����
    auto btn_help = btn_create(
        "MapChoose/contents/btn_help_normal.png",
        "MapChoose/contents/btn_help_pressed.png",
        "MapChoose/contents/btn_help_normal.png",
        po_btn_help, 2, 1.2);
    //��ʼ
    auto btn_start = btn_create(
        "MapChoose/contents/btn_start_normal.png",
        "MapChoose/contents/btn_start_pressed.png",
        "MapChoose/contents/btn_start_normal.png",
        po_btn_start, 3);

    return true;
}