#pragma once

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/* 应用程序 */
//继承private，保留不可见部分
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();


    //初始化导演和场景
    //返回：初始化成功与否
    virtual bool applicationDidFinishLaunching();

    //程序进入后台后调用
    virtual void applicationDidEnterBackground();

    //程序进入前台前调用
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

