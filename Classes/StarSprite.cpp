//
//  StarSprite.cpp
//  PopStar
//
//  Created by mac on 16/6/22.
//
//

#include "StarSprite.hpp"

USING_NS_CC;

Star* Star::createStar(int number, int width, int height, float x, float y)
{
    auto star = new Star();
    if (star && star->init()) {
        star->autorelease();
        star->enemyInit(number, width, height, x, y);
        return star;
    }
    else {
        CC_SAFE_DELETE(star);
        return nullptr;
    }
}

void Star::enemyInit(int number, int width, int height, float x, float y)
{
    _number = number;
    _starX = 0;
    _starY = 0;
    
    _layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), width-2, height-2);
    _layerColorBG->setPosition(x, y);
    this->addChild(_layerColorBG);
}

void Star::setNumber(int number)
{
    _number = number;
    
    switch (number) {
        case -1:
            _layerColorBG->setColor(Color3B(200, 190, 180));
            break;
        case 0:
            _layerColorBG->setColor(Color3B(250, 230, 40));
            break;
        case 1:
            _layerColorBG->setColor(Color3B(40, 180, 250));
            break;
        case 2:
            _layerColorBG->setColor(Color3B(130, 220, 110));
            break;
        case 3:
            _layerColorBG->setColor(Color3B(250, 80, 130));
            break;
        case 4:
            _layerColorBG->setColor(Color3B(180, 50, 250));
            break;
            
        default:
            _layerColorBG->setColor(Color3B(200, 190, 180));
            break;
    }
}