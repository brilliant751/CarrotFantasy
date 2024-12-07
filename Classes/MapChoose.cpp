
#include "EnterScene.h"
#include "MapChoose.h"
#include "HelpScene_1.h"
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

/* �����ť�л���һ��map */
void MapChoose::left_onButtonClicked(Ref* sender) {
    if (level > 0) {
        cur_map->setSpriteFrame(all_map[--level].map_url);
        towers->setSpriteFrame(all_map[level].towers_url);
        waves->setSpriteFrame(all_map[level].waves_url);
    }
}

/* �Ҽ���ť�л���һ��map */
void MapChoose::right_onButtonClicked(Ref* sender) {
    if (level < 2) {
        cur_map->setSpriteFrame(all_map[++level].map_url);    
        towers->setSpriteFrame(all_map[level].towers_url);
        waves->setSpriteFrame(all_map[level].waves_url);
    }
}

/* ������ť�л���HelpScene_1 */
void MapChoose::help_onButtonClicked(Ref* sender) {
    auto next = HelpScene_1::create_Scene();
    Director::getInstance()->pushScene(next);
}

/* ���ذ�ť���ص�EnterScene */
void MapChoose::back_onButtonClicked(Ref* sender) {
    Director::getInstance()->popScene();
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
    //                         4 - left
    //                         5 - right
    auto btn_create = [&](const string& normal_name, const string& pressed_name, const string& locked_name,
        const Vec2& pos, int btn_type, const float& scale = 1.1f, int layer = 0) {
            auto temp_btn = Button::create(normal_name, pressed_name, locked_name);
            temp_btn->setPosition(pos);
            temp_btn->setScale(scale);

            temp_btn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        switch (btn_type) {
                            case 1:
                                back_onButtonClicked(this);//�ص�EnterScene
                                break;
                            case 2: 
                                help_onButtonClicked(this);                              
                                break;
                            case 3:
                                //��ʼ��Ϸ
                                break;
                            case 4:
                                left_onButtonClicked(this);
                                break;
                            case 5:
                                right_onButtonClicked(this);
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
    const Vec2 po_map(980, 560);           //���÷�����λ��
    const Vec2 po_towers(980, 240);        //���÷�����λ��
    const Vec2 po_waves(1180, 850);        //���÷�����λ��
    constexpr float btn_scale = 1.1f;      //��ť�Ŵ���
    constexpr float map_scale = 1.5f;      //��ͼ�Ŵ���
    const Vec2 po_bg_left(495, 185);       //���±���λ��
    const Vec2 po_bg_right(1482, 183);     //���±���λ��
    const Vec2 po_btn_back(330, 953);      //���ذ�ťλ��
    const Vec2 po_btn_help(1628, 953);     //������ťλ��
    const Vec2 po_btn_start(980, 150);     //��ʼ��ťλ��
    const Vec2 po_btn_left(400, 560);      //���ư�ťλ��
    const Vec2 po_btn_right(1560, 560);    //���ư�ťλ��


    /**************************************/

    /* �������� */
    auto bg = sp_create("bg.png", po_bg, map_scale, -1);
    auto bg_left = sp_create("bg_left.png", po_bg_left, map_scale, 0);
    auto bg_right = sp_create("bg_right.png", po_bg_right, map_scale, 0);

    /* ����cur_map towers waves */
    cur_map = sp_create(all_map[level].map_url, po_map, 1.7, 0);
    towers = sp_create(all_map[level].towers_url, po_towers, map_scale, 0);
    waves = sp_create(all_map[level].waves_url, po_waves, map_scale, 0);

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
    //����
    auto btn_left = btn_create(
        "MapChoose/contents/btn_left_normal.png",
        "MapChoose/contents/btn_left_pressed.png",
        "MapChoose/contents/btn_left_normal.png",
        po_btn_left, 4);
    //����
    auto btn_right = btn_create(
        "MapChoose/contents/btn_right_normal.png",
        "MapChoose/contents/btn_right_pressed.png",
        "MapChoose/contents/btn_right_normal.png",
        po_btn_right, 5);
    
   


    return true;
}