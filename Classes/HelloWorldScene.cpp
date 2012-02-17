#include "HelloWorldScene.h"
#define PTM_RATIO 32.0
USING_NS_CC;
static CCPoint convertCoordinate(CCPoint point)
{
    return CCDirector::sharedDirector()->convertToGL(point);
}
CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);
	////////////////////////////////////
    //Create and add the user interface
    ////////////////////////////////////

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	userInterfaceLayer = UserInterfaceLayer::node();
    this->addChild(userInterfaceLayer,2);
	userInterfaceLayer->setUserData(this);
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	/////////////////////////////
	// enables multitouch
	this->setIsTouchEnabled(true);
	userInterfaceLayer->changeup(10);

	
	/////////////////////////////
	// Creates a b2World
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	myWorld = new b2World(gravity);

	// Create edges around the entire screen
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
	b2Body *groundBody = myWorld->CreateBody(&groundBodyDef);
	b2EdgeShape groundBox;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundBox;
	groundBox.Set(b2Vec2(0,0), b2Vec2(CCDirector::sharedDirector()->getWinSize().width/PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
	groundBox.Set(b2Vec2(0,0), b2Vec2(0, CCDirector::sharedDirector()->getWinSize().height/PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	groundBox.Set(b2Vec2(0, CCDirector::sharedDirector()->getWinSize().height/PTM_RATIO), 
	b2Vec2(CCDirector::sharedDirector()->getWinSize().width/PTM_RATIO, CCDirector::sharedDirector()->getWinSize().height/PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);
	groundBox.Set(b2Vec2(CCDirector::sharedDirector()->getWinSize().width/PTM_RATIO, 
	CCDirector::sharedDirector()->getWinSize().height/PTM_RATIO), b2Vec2(CCDirector::sharedDirector()->getWinSize().width/PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
	 

	zmogus = new Person("Target.png",100,100,36,24,20,1,this,myWorld);



	/////////////////////////////
	// 3. add your codes below...

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::spriteWithFile("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	this->schedule( schedule_selector(HelloWorld::tick));
	
	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	CCSetIterator it = pTouches->begin();
    CCPoint pt;
    CCTouch* touch;

    for( int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++ )
    {
        touch = (CCTouch*)(*it);
        pt = touch->locationInView( touch->view() );
        it++;
		zmogus->move(pt);
		zmogus->rotateTo(pt);
		userInterfaceLayer->changeup(pt.x);
	}
}

void HelloWorld::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	CCSetIterator it = pTouches->begin();
    CCPoint pt;
    CCTouch* touch;

    for( int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++ )
    {
        touch = (CCTouch*)(*it);
        pt = touch->locationInView( touch->view() );
        it++;
	}
}
void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent )
{
	CCSetIterator it = pTouches->begin();
    CCPoint pt;
    CCTouch* touch;

    for( int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++ )
    {
        touch = (CCTouch*)(*it);
        pt = touch->locationInView( touch->view() );
        it++;
	}
}

void HelloWorld::tick(ccTime dt)
{
	myWorld->Step(1.0/60,8,1);
	for(b2Body *b = myWorld->GetBodyList(); b; b=b->GetNext())
	{    
        if (b->GetUserData() != NULL)
		{
			CCSprite *ballData = (CCSprite*)((Person *)b->GetUserData())->getSprite();//b->GetUserData();
			ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
			ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }        
    }
	zmogus->movement();
}