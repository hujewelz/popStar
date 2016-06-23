#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "StarSprite.hpp"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void autoCreateStars(cocos2d::Size size, cocos2d::Vec2 origin);
    // implement the "static create()" method manually
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    CREATE_FUNC(HelloWorld);
private:
   
    std::vector< cocos2d::Vector<Star*> > _starVector;
    
    Star* getStar(cocos2d::Point touchP);
    
    //存放点击的star
    cocos2d::Vector<Star*> _starsAround;
    
    //获取点击star周围的star
    cocos2d::Vector<Star*> checkStarAround(Star* star);
    
    //检测所有与点击star相邻的star
    void checkStarAllAround(cocos2d::Vector<Star*> starsAround);
    
    void reDiessStar();
    void reDiessStarRun(int x);
    
    void reDiessStarRt();
    
    bool gameOver();
};

#endif // __HELLOWORLD_SCENE_H__
