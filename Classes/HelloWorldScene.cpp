#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("pop star", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height+10));

    this->addChild(label, 1);


    
    auto bg = LayerColor::create(Color4B(180, 170, 160, 255));
    this->addChild(bg,-1);
    
    autoCreateStars(visibleSize, origin);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Point touchP = touch->getLocation();
    
    Star *star = getStar(touchP);
    if (star == NULL) {
        return false;
    }
    
    _starsAround = checkStarAround(star);
    if (_starsAround.size() >= 2) {
        checkStarAllAround(_starsAround);
    }
    else {
        return true;
    }
    
    return true;
}

void HelloWorld::checkStarAllAround(cocos2d::Vector<Star*> starsAround)
{
    Vector<Star*> newStars;
    
    for (int i=0; i<starsAround.size(); i++) {
        Star *oldStar = starsAround.at(i);
        Vector<Star*> newAround = checkStarAround(oldStar);
        
        for (int j=0; j<newAround.size(); j++) {
            bool isSaved = false;
            Star *newStar = newAround.at(j);
            
            for (int k=0; k<_starsAround.size(); k++) {
                Star *star = _starsAround.at(k);
                
                if ((newStar->getStarX()==star->getStarX()) && (newStar->getStarY()==star->getStarY())) {
                    isSaved = true;
                    break;
                }
            }
            
            if (!isSaved) {
                newStars.pushBack(newStar);
            }
        }
    }
    
    if (newStars.size() > 0) {
        for (Star* star : newStars) {
            _starsAround.pushBack(star);
        }
        checkStarAllAround(newStars);
    }
    else {
        for (Star* star : _starsAround) {
            star->setNumber(-1);
        }
        
        //移动空白上方star
        reDiessStar();
       
    }
    
}

Vector<Star*> HelloWorld::checkStarAround(Star* star)
{
    Vector<Star*> stars;
    bool isDoubleStar = false;
    
    //判断点击位置往上的相同数
    int y = star->getStarY();
    for (int upY=y+1; upY<10; upY++) {
        Star *temp = _starVector.at(star->getStarX()).at(upY);
        if (temp->getNumber() == star->getNumber()) {
            stars.pushBack(temp);
            isDoubleStar = true;
        }
        else {
            break;
        }
    }
    //判断点击位置往下的相同数
    for (int downY=y-1; downY>=0; downY--) {
        Star *temp = _starVector.at(star->getStarX()).at(downY);
        if (temp->getNumber() == star->getNumber()) {
            stars.pushBack(temp);
            isDoubleStar = true;
        }
        else {
            break;
        }
    }
    
    //判断点击位置往左的相同数
    int x = star->getStarX();
    for (int leftX=x-1; leftX>=0; leftX--) {
        Star *temp = _starVector.at(leftX).at(star->getStarY());
        if (temp->getNumber() == star->getNumber()) {
            stars.pushBack(temp);
            isDoubleStar = true;
        }
        else {
            break;
        }
    }

    //判断点击位置往右的相同数
    for (int rightX=x+1; rightX<10; rightX++) {
        Star *temp = _starVector.at(rightX).at(star->getStarY());
        if (temp->getNumber() == star->getNumber()) {
            stars.pushBack(temp);
            isDoubleStar = true;
        }
        else {
            break;
        }
    }
    if (isDoubleStar) {
        stars.pushBack(star);
       
    }
    
    return stars;
}

void HelloWorld::reDiessStar()
{
    for (int x=0; x<10; x++) {
        reDiessStarRun(x);
    }
    
    reDiessStarRt();
    gameOver();
}

void HelloWorld::reDiessStarRun(int x)
{
    //检测出每列的空格数
    int number = 0;
    for (int k=0; k<10; k++) {
        if (_starVector.at(x).at(k)->getNumber() == -1) {
            number++;
        }
    }
    
    //判断空格是否大于1
    if (number > 0 ) {
        
        for (int y=0; y<10; y++) {
            if (_starVector.at(x).at(y)->getNumber() == -1) {
                if (10 - _starVector.at(x).at(y)->getStarY() > number) {
                    for (int i=y; i<10; i++) {
                        if (i+1 == 10) { //最后一个
                            _starVector.at(x).at(i)->setNumber(-1);
                        }
                        else{ //向下移一个
                            
                            _starVector.at(x).at(i)->setNumber(_starVector.at(x).at(i+1)->getNumber());
                        }
                    }
                 reDiessStarRun(x);
                }
                else{
                    break;
                }
            }
        }
    }
}

void HelloWorld::reDiessStarRt()
{
    for (int x=0; x<10; x++) {
        int number = 0;
        for (int k=0; k<10; k++) {
            if (_starVector.at(x).at(k)->getNumber() == -1) {
                number++;
            }
        }
        
        if (number == 10) {
            for (int y=0; y<10; y++) {
                for (int s=x; s<9; s++) {
                    _starVector.at(s).at(y)->setNumber( _starVector.at(s+1).at(y)->getNumber());
                    _starVector.at(s+1).at(y)->setNumber(-1);
                }
            }
        }
        
    }
}

bool HelloWorld::gameOver()
{
    bool isGameOver = true;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            Star *star = _starVector.at(i).at(j);
            if (checkStarAround(star).size()>0 && star->getNumber()!=-1) {
                isGameOver = false;
                break;
            }
        }
        
        if (!isGameOver) {
            break;
        }
    }
    
    if (isGameOver) {
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
    }
    return isGameOver;
}

Star* HelloWorld::getStar(cocos2d::Point touchP)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int w = (visibleSize.width - 10) / 10;
    
    //求出点击的x的位置
    float x = (touchP.x - 5 - origin.x) / w;
    float y = (touchP.y - visibleSize.height/10 -origin.y) / w;
    
    if (x<10 && y<10 && x>=0 && y>=0) {
        int x = (touchP.x - 5 - origin.x) / w;
        int y = (touchP.y - visibleSize.height/10 -origin.y) / w;
        return _starVector.at(x).at(y);
    }
    else {
        return NULL;
    }
}

void HelloWorld::autoCreateStars(Size size, Vec2 origin)
{
    //计算每个方格的大小
    int w = (size.width - 10) / 10;
    
    for (int i=0; i<10; i++) {
        Vector<Star*> starVectorJ;
        for (int j=0; j<10; j++) {
            int maxX = 5, minX = 0;
            
            int rangeX = maxX - minX;
            int actualX = rand()%rangeX + minX;
            
            Star* star = Star::createStar(-1, w, w,
                                         origin.x + i * w + 5,
                                         origin.y + w * j + size.height/10);
            star->setStarX(i);
            star->setStarY(j);
            star->setNumber(actualX);
            this->addChild(star);
            
            starVectorJ.pushBack(star);
        }
        
        _starVector.push_back(starVectorJ);
    }
    
}



