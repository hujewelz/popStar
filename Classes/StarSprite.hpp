//
//  StarSprite.hpp
//  PopStar
//
//  Created by mac on 16/6/22.
//
//

#ifndef StarSprite_hpp
#define StarSprite_hpp

#include "cocos2d.h"

class Star : public cocos2d::Sprite {
public:
    static Star* createStar(int number, int width, int height, float x, float y);
    
    //获取颜色
    int getNumber()
    {
        return _number;
    }
    
    void setNumber(int number);
   
    //获取色块的坐标
    cocos2d::Point getColorBGPoint()
    {
        return _layerColorBG->getPosition();
    }
    
    int getStarX()
    {
        return _starX;
    }
    
    int getStarY()
    {
        return _starY;
    }
    
    void setStarX(int x)
    {
        _starX = x;
    }
    
    void setStarY(int y)
    {
        _starY = y;
    }
    
private:
    //显示的颜色
    int _number;
    //获取star的位置
    int _starX, _starY;
    
    void enemyInit(int number, int width, int height, float x, float y);
    
    cocos2d::LayerColor* _layerColorBG;
    
};

#endif /* StarSprite_hpp */
