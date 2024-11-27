#pragma once

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/* Ӧ�ó��� */
//�̳�private���������ɼ�����
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();


    //��ʼ�����ݺͳ���
    //���أ���ʼ���ɹ����
    virtual bool applicationDidFinishLaunching();

    //��������̨�����
    virtual void applicationDidEnterBackground();

    //�������ǰ̨ǰ����
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

