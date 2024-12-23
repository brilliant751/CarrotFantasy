
#include "GameMenu.h"
#include "Skyline_01.h"
#include "Skyline_02.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;
using namespace ui;
using namespace std;

extern bool is_stop;    //�����Ϸ�Ƿ���ͣ
extern Target* target;

/* ����Layer */
Layer* PauseMenu::create_Layer()
{
    return PauseMenu::create();
}

Layer* CountDown::create_Layer()
{
    return CountDown::create();
}

/* ��ʼ�� */
bool PauseMenu::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(2050��1200)

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

    constexpr float btn_scale = 1.5f;       //��ť�Ŵ���
    constexpr float map_scale = 1.5f;       //��ͼ�Ŵ���
    constexpr float word_scale = 2.0f;      //���ַŴ���
    const Vec2 bg(visibleSize / 2);         //����λ��
    const Vec2 ctn(796, 607);              //������ťλ��
    const Vec2 rst(796, 495);              //������ťλ��
    const Vec2 bck(796, 383);              //������ťλ��

    /**************************************/

    /*********** �������� **********/
    /* �������ڱ��� */
    auto menu_bg = sp_create("options_bg.png", bg, map_scale, -1);


    /*********** ������ť **********/
    /* ���� ������Ϸ ��ť */
    auto resume = btn_create(
        "Levels/btn/continue_normal.png",
        "Levels/btn/continue_pressed.png",
        ctn, btn_scale, 1);
    resume->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                main_scene->removeChildByName("dimmer");    //��ȥ������
                main_scene->removeChild(this);      //�رյ���
                // �ָ��������ļ����¼�
                main_scene->getEventDispatcher()->resumeEventListenersForTarget(main_scene, true);
                // �ָ���������ˢ�ºͶ���
                main_scene->resumeSchedulerAndActions();
                is_stop = false;    //��ǿ�ʼ
                break;
            default:
                break;
        }
        });

    /* ���� ���¿�ʼ ��ť */
    auto restart = btn_create(
        "Levels/btn/restart_normal.png",
        "Levels/btn/restart_pressed.png",
        rst, btn_scale, 1);
    restart->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                main_scene->removeChildByName("dimmer");    //��ȥ������
                main_scene->removeChild(this);      //�رյ���
                //todo:���¿�ʼ 
                /* �ָ��������ļ����¼� */
                main_scene->getEventDispatcher()->resumeEventListenersForTarget(main_scene, true);
                break;
            default:
                break;
        }
        });
    
    /* ���� ѡ��ؿ� ��ť */
    auto back = btn_create(
        "Levels/btn/return_normal.png",
        "Levels/btn/return_pressed.png",
        bck, btn_scale, 1);
    back->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:      
                /* ����MapChoose */
                Director::getInstance()->popScene();
                break;
            default:
                break;
        }
        });
    return true;
}

/* ��ʼ�� */
bool CountDown::init() {
    if (!Layer::init())
        return false;

    /* ��ʼ���ֲ����� */
    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)
    const Vec2 po = (visibleSize / 2);  //����ʱλ��
    const float scale = 1.5f;       //�Ŵ���

    //����url
    string count_url[3] = {
        "start_time_1.png","start_time_2.png","start_time_3.png"
    };

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
    
    /*********** �������� **********/
    /* �����װ� */
    auto back = sp_create("start_time_bg.png", po, scale, 0);
    /* ����ȦȦ */
    auto lightning = sp_create("start_lightning.png", po, scale, 1);
    lightning->setAnchorPoint(Vec2(0.5, 0.5));
    /* �������� */
    count = sp_create(count_url[co], po, scale, 1);
    count->setName("count");

    /*********** �������� **********/
    /* תȦȦ */
    auto roll = Sequence::create(RotateBy::create(3.0f, -1080.0f),nullptr);
    lightning->runAction(roll);
    /* ����ʱ */
    auto delay = DelayTime::create(0.8f);   //ͣ��
    auto scaleTo = ScaleTo::create(0.2f, 0.0f);     //��С
    auto scaleBack = ScaleTo::create(0.01f, 1.0f);  //���
    // �л�����
    auto change = CallFunc::create([this]() {
        auto sp = (Sprite*)(this->getChildByName("count"));
        if (co >= 1) {
            co--;
            sp->setSpriteFrame(this->count_url[co]);
            auto scaleTo = ScaleTo::create(1.0f, 0.0f);           
        }
        else 
            Director::getInstance()->getRunningScene()->removeChild(this);
        });
    // һ���л�
    auto action_sequence = Sequence::create(delay,scaleTo, change, scaleBack, nullptr);
    // �ظ�����
    auto rep = Repeat::create(action_sequence, 3);
    // ����������
    auto ban = CallFunc::create([]() {
        /* ��ͣ�������Ļ */
        auto cur_scene = Director::getInstance()->getRunningScene();
        // �˴���ѭ����ͣ����child���ļ����¼�
        cur_scene->getEventDispatcher()->pauseEventListenersForTarget(cur_scene, true);
        // ��ͣ��������ˢ�ºͶ���
        cur_scene->pauseSchedulerAndActions();
        is_stop = true;     //�����ͣ
        });
    auto resume= CallFunc::create([]() {
        /* �ָ��������Ļ */
        auto cur_scene = Director::getInstance()->getRunningScene();
        // �˴���ѭ���ָ�����child���ļ����¼�
        cur_scene->getEventDispatcher()->resumeEventListenersForTarget(cur_scene, true);
        // ��ͣ��������ˢ�ºͶ���
        cur_scene->resumeSchedulerAndActions();
        is_stop = false;    // ��ǿ�ʼ
        });
    // ��������
    auto all_sequence = Sequence::create(ban, rep, resume, nullptr);
    // ����
    count->runAction(all_sequence);

    return true;
}

/* ����Ѫ�� */
void Target::create_slider()
{
    auto scene = (Scene*)getParent();
    Vec2 pos = this->getPosition();
    pos.y += 70;
    hp_slider = LoadingBar::create();
    hp_slider->loadTexture("Monsters/contents/hp_slider.png");
    hp_slider->setScale(1.5f);
    hp_slider->setPercent(100.0f);
    hp_slider->setPosition(pos);
    hp_slider->setAnchorPoint(Vec2(0.5f, 1.0f));
    scene->addChild(hp_slider, 4);
    hp_holder = sp_create(scene, "hp_holder.png", pos, 1.5f, 3);
    hp_holder->setAnchorPoint(Vec2(0.5f, 1.0f));
    selected = sp_create(scene, "selected.png", pos, 1.5f, -5);
    selected->setAnchorPoint(Vec2(0.5f, 0.0f));
}

void Target::get_hurt(int damage)
{
    hp -= damage;
    float percent = hp / max_hp * 100;
    if (hp <= 0)
    {
        extern int money;
        extern Monster* cur_mons[20];
        money += reward;;	//������Ǯ
        if (get_type()) {
            cur_mons[this->getTag() % 100 - 1] = NULL;
            AudioEngine::play2d("sound/monster0.mp3", false);
        }
        if (target == this)
            target = NULL;
        this->selected->removeFromParentAndCleanup(true);
        this->hp_slider->removeFromParentAndCleanup(true);
        this->hp_holder->removeFromParentAndCleanup(true);
        this->removeFromParentAndCleanup(true);
        return;
    }
    hp_slider->setPercent(percent);
}
