
#include "Towers.h"
#include "tools.h"
#include "ui/UIButton.h"
#include "AudioEngine.h"
#define NULL 0
USING_NS_CC;
using namespace ui;
using namespace std;

extern int waves;   //���ﲨ��
extern int speed;   //��Ϸ�ٶ�
extern Monster* cur_mons[20];   //���Ϲ���
extern int lives;   //���Ϲ�������
extern Target* target;

/* ���������� */
Tower* Tower::create_Tower(int type, int line, int row, Scene* scene)
{
    Vec2 pos = get_po(line, row);
    auto building = Tower::create();
    building->setType(towers[type]);
    building->type = type;
    building->base = Sprite::create();
    building->bullet = Sprite::create();
    building->_setScale(1.5, 1.5, 1.5);
    building->_setPosition(pos);
    building->_setSpriteFrame();
    scene->addChild(building, 3);
    scene->addChild(building->base, 2);
    scene->addChild(building->bullet, -10);

    return building;
}

/* �������� */
void Tower::_setPosition(const Vec2& pos)
{
    this->setPosition(pos);
    this->base->setPosition(pos);
    this->bullet->setPosition(pos);
}

/* ���þ���ͼƬ */
void Tower::_setSpriteFrame() {
    this->setSpriteFrame(this->info.origin_url[this->level]);
    this->base->setSpriteFrame(this->info.D[this->level]);
    this->bullet->setSpriteFrame(this->info.bullet_url[this->level]);
}

/* ���÷Ŵ��� */
void Tower::_setScale(const float& building_scale, const float& base_scale, const float& bullet_scale) {
    this->setScale(building_scale);
    this->base->setScale(base_scale);
    this->bullet->setScale(bullet_scale);
}

/* �������� */
void Tower::up_level() {
    level++;
    if (this->type == 2) {
        this->unschedule(schedule_selector(Tower::shoot_3));
        this->schedule(schedule_selector(Tower::shoot_3), this->info.speed[level] / speed);
    }
    else {
        this->unschedule(schedule_selector(Tower::shoot_1_2));
        this->schedule(schedule_selector(Tower::shoot_1_2), this->info.speed[level] / speed);
    }
    this->setSpriteFrame(this->info.origin_url[level]);
    this->base->setSpriteFrame(this->info.D[level]);
    this->bullet->setSpriteFrame(this->info.bullet_url[level]);
}

int Tower::tower_rotate_direction() {
    Monster* mon = this->get_first_monster();
    if (mon == nullptr)
        return 0;//����ת

    Vec2 po1 = this->getPosition();
    Vec2 po2 = mon->getPosition();

    float mon_angle = cal_relative_angle(po1, po2);
    float tower_angle = this->get_angle();

    //return mon_angle;
    /* �ж���ת���� */
    if (fabs(mon_angle - tower_angle) <= 3)
        return 0;//����ת

    int clock_wise = 0;//˳ʱ��Ϊ1 ��ʱ��Ϊ-1

    if (mon_angle >= 0 && mon_angle <= 180) {
        if (tower_angle >= mon_angle && tower_angle <= mon_angle + 180)
            clock_wise = 3;
        else
            clock_wise = -3;
    }
    else {
        if (tower_angle >= mon_angle - 180 && tower_angle <= mon_angle)
            clock_wise = -3;
        else
            clock_wise = 3;
    }

    return -clock_wise;//��ʱ��Ϊ������
}

Monster* Tower::get_first_monster() {//��ȡ��Χ�ڵ�һ��Montser
    for (int i = 0; i < lives; ++i)
        if (cur_mons[i]) {
            float d = cal_distance(this->getPosition(), cur_mons[i]->getPosition());
            if (d <= this->info.radius[this->get_level()])
                return cur_mons[i];
        }
    return NULL;
}

void Tower::tower_rotate_1(float dt) {
    //int direc = tower_rotate_direction();//��ʱ��Ϊ������
    //if (direc == 0)
    //    return;
    //float de = direc - angle;
    //float change = 0;
    //if (de > 180)
    //    change = 3;
    //else if (de <= 180 && de > 3)
    //    change = -3;
    //else if (de <= 3 && de >= -3)
    //    change = -de;
    //else if (de < -3 && de >= -180)
    //    change = 3;
    //else if (de < -180)
    //    change = -3;
    //float change_angle = 2.0f * direc;
    //float next_ag = angle + change_angle;
    ////float next_ag = angle + change;

    //if (next_ag >= 360)
    //    next_ag -= 360;
    //else if (next_ag < 0)
    //    next_ag += 360;
    //angle = next_ag;

    //this->setRotation(next_ag);
    //this->bullet->setRotation(next_ag);
    //this->setRotation(change_angle);
    //this->bullet->setRotation(change_angle);
}

void Tower::shoot_1_2(float dt) {
    Vec2 po1 = this->getPosition();//�ӵ���ʼ����
    Target* mon = NULL;//Tower��ʱ��������
    if (target) {//���ж���û��ѡ�ж����Լ��Ƿ��ڷ�Χ��
        float d = cal_distance(po1, target->getPosition());//�������
        if (d <= this->info.radius[this->get_level()])//�ڷ�Χ��
            mon = target;
        else //Ѱ���ڷ�Χ�ڵĵ�һ������
            mon = this->get_first_monster();
    }
    else //Ѱ���ڷ�Χ�ڵĵ�һ������
        mon = this->get_first_monster();
    if (!mon)//�޹���Ͳ�����
        return;
    /* ���ڷ�Χ�ڵĹ��� �����ӵ� ��ת*/
    Vec2 po2 = mon->getPosition();
    float angle = -cal_relative_angle(po1, po2);
    if (this->get_type() == 0) {
        auto rotate = RotateTo::create(0.0f, angle);
        this->runAction(rotate);//���� 
    }
    this->biu_1_2(po1, mon->getTag(),angle);
}

void Tower::shoot_3(float dt) {//���� 0.4s 2��     5/60=1/12 ��   ÿ1/60s
    Vec2 po1 = this->getPosition();//�ӵ���ʼ����
    Target* mon = NULL;//Tower��ʱ��������
    if (target) {//���ж���û��ѡ�ж����Լ��Ƿ��ڷ�Χ��
        float d = cal_distance(po1, target->getPosition());//�������
        if (d <= this->info.radius[this->get_level()])//�ڷ�Χ��
            mon = target;
        else //Ѱ���ڷ�Χ�ڵĵ�һ������
            mon = this->get_first_monster();
    }
    else //Ѱ���ڷ�Χ�ڵĵ�һ������
        mon = this->get_first_monster();
    if (!mon)//�޹���Ͳ�����
        return;
    /* ���ڷ�Χ�ڵĹ��� �����ӵ� */
    Vec2 po2 = mon->getPosition();//��������
    //���� �ӵ�ָ�����
    float x = po2.x - po1.x;//����x����
    float y = po2.y - po1.y;//����y����

    float d = cal_distance(po1, po2);//��������

    float beilv = 1.0f / 12 * 95 / d;//����Ҫ��1/60s�߶೤ ������ ��beilv*d=1/150*95
    this->biu_fan(po1, x * beilv, y * beilv);
}

void Tower::biu_fan(Vec2& start, float x, float y) {
    /* �����ӵ� ����ʼ�� */
    auto biu = Sprite::create();
    biu->setPosition(start);
    biu->setScale(1.5f);
    biu->setSpriteFrame(this->get_bullet_url());
    biu->setTag(0);
    auto scene = Director::getInstance()->getRunningScene();
    scene->addChild(biu, 4);
    auto rotate = RotateBy::create(1.0f / 60, 30.0f);
    auto ahead = MoveBy::create(1.0f / 60, Vec2(x, y));
    //auto delay = DelayTime::create(0.2f);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 10; j++)
            attacked[i][j] = 0; 
    auto call_check = CallFunc::create([this,scene=scene, biu = biu]() {
        Vec2 cur_pos = biu->getPosition();
        for (int i = 0; i < lives; i++)
            if (cur_mons[i] && cur_mons[i]->getBoundingBox().containsPoint(cur_pos) && !attacked[0][i]) {
                cur_mons[i]->get_hurt(this->get_info().attack[this->get_level()]);
                attacked[0][i] = 1;
            }
        for (int i = 0; i < 10; i++) {
            auto sp = scene->getChildByTag<Target*>(300001 + i);
            if (sp && sp->getBoundingBox().containsPoint(cur_pos) && !attacked[1][i]) {
                sp->get_hurt(this->get_info().attack[this->get_level()]);
                attacked[1][i] = 1;
            }
        }
        if (cur_pos.x >= 1380 || cur_pos.x <= 240 || cur_pos.y >= 860 || cur_pos.y <= 100)
            biu->removeFromParentAndCleanup(true);
        });
    //auto seq = Sequence::create(delay, call_check, nullptr);
    //auto spawn = Spawn::create(rotate, ahead, seq, nullptr);
    auto spawn = Spawn::create(rotate, ahead, call_check, nullptr);

    auto repeat = RepeatForever::create(spawn);
    biu->runAction(repeat);
}

// bottle shit�ӵ�������ʼλ��(Towerλ��) �������
void Tower::biu_1_2(Vec2& start, const int tag, float angle) {
    /* ʵʱ�任������ӵ����� */
    //��������ʼ��
    auto biu = Sprite::create();
    biu->setPosition(start);
    biu->setScale(1.5f);
    biu->setSpriteFrame(this->get_bullet_url());
    auto scene = Director::getInstance()->getRunningScene();
    
    auto rotate = RotateTo::create(0.0f, this->get_type() == 0 ? angle : angle - 180);
    biu->runAction(rotate);
    scene->addChild(biu, 2);

    float slow = this->get_info().slow_down[this->get_level()];//���ٰٷֱ�
    float duration = this->get_info().duration[this->get_level()];//���ٳ���ʱ��
    float attack = this->get_info().attack[this->get_level()];//�˺�
    int tower_type = this->get_type();
    //this, scene = scene, biu = biu, tag = tag,slow=slow,duration=duration,tower_type=tower_type
    auto call_check = CallFunc::create([=]() {
        Vec2 po1 = biu->getPosition();
        auto p = scene->getChildByTag<Monster*>(tag);
        if (!p) {//����Ŀ�����ӵ�����ǰ�ҵ���or�����Ͳ�����
            biu->removeFromParentAndCleanup(true);//�ӵ�ԭ����ʧ
            return;
        }
        else if (p->getBoundingBox().containsPoint(po1)) {//�ӵ����﷢��Ŀ��
            if (tower_type == 1 && p->get_type() == 1) //shit ���� ����
                p->set_sp_percent(slow,duration);
            p->get_hurt(attack);//�˺�
            //����Ч��todo
            biu->removeFromParentAndCleanup(true);//��ʧ
            return;
        }
        //�Ȳ��ܽǶ���
        // �ӵ���û�����ҷ���Ŀ�����
        //���� �ӵ�ָ�����
        int target_type = p->get_type();//��ȡĿ������ ������׼

        Vec2 po2 = p->getPosition();
        float x = po2.x - po1.x;//����x����
        float y = po2.y - po1.y + 40 * target_type;//����y����

        float d = cal_distance(po1, po2);//��������

        float beilv = 1.0f / 8 * 95 / d;//����Ҫ��1/60s�߶೤ ������ ��beilv*d=1/150*95
        auto ahead = MoveBy::create(1.0f / 60, Vec2(x * beilv, y * beilv));//һ֡���˶�
        biu->runAction(ahead);//ִ��
        });

    //auto del
    auto delay = DelayTime::create(1.5f / 60);
    auto seq = Sequence::create(call_check, delay, nullptr);
    auto repeat = RepeatForever::create(seq);
    biu->runAction(repeat);

}

/* �����ʼ�� */
bool Tower::init()
{
    if (!Sprite::init())
        return false;
    return true;
}