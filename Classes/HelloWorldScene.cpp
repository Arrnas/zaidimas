#include "HelloWorldScene.h"

#define PTM_RATIO 32.0
USING_NS_CC;
const CCPoint trigger(20,20);
const double triggerRadius = 20;

static CCPoint convertCoordinate(CCPoint point)
{
    return CCDirector::sharedDirector()->convertToGL(point);
}
static bool isPointInCircle(CCPoint point, CCPoint center, float radius)
{
	float dx = (point.x - center.x);
	float dy = (point.y - center.y);
    return (radius >= sqrt((dx*dx)+(dy*dy)));
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
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("atlas.plist");

	
	/////////////////////////////
	// Creates a b2World
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	myWorld = new b2World(gravity);
	myWorld->SetContactListener(this);

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
	 

	zmogus = new Person("sprite",100,100,46,95,20,1,this,myWorld,"atlas.png");
	zmogus->shootingAnim();
	finger = NULL;
	destroyBullet = NULL;
	hitBody = NULL;
	score = 0;
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
	this->schedule( schedule_selector(HelloWorld::tock),5.0);
	
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
        pt = convertCoordinate(touch->locationInView( touch->view() ));
        it++;
		if(isPointInCircle(pt,trigger,triggerRadius))
		{
			finger = touch;
		}
		else
		{
			if(finger == NULL)
			{
				zmogus->move(pt);
				zmogus->rotateTo(pt);
			}
			else
			{
				zmogus->rotateTo(pt);
				zmogus->changeAnimation(2);
				zmogus->shoot(pt);
			}
		}
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
        pt = convertCoordinate(touch->locationInView( touch->view() ));
        it++;
		if(finger == NULL)
		{
			zmogus->move(pt);
			zmogus->rotateTo(pt);
		}
		else
		{
			if(touch == finger)
			{
				if(!isPointInCircle(pt,trigger,triggerRadius))
					finger = NULL;
			}
			else
			{
				zmogus->rotateTo(pt);
			}
		}

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
        pt = convertCoordinate(touch->locationInView( touch->view() ));
        it++;
		if(touch == finger)
			finger = NULL;
	}
}
void HelloWorld::tock(ccTime dt)
{
	enemy = new Person("sprite",rand()%600,rand()%600,46,95,20,1,this,myWorld,"atlas.png");
}
void HelloWorld::tick(ccTime dt)
{
	if(destroyBullet != NULL)
	{
		zmogus->deleteBullet(((bullet *)destroyBullet->GetUserData())->getId());
		destroyBullet = NULL;
	}
	if(hitBody != NULL)
	{
		if(((Person *)hitBody->GetUserData())->getHP() > 1)
			((Person *)hitBody->GetUserData())->hit(hitPos);
		else
		{
			((Person *)hitBody->GetUserData())->~Person();
			userInterfaceLayer->changeup(++score);
		}
		hitBody = NULL;
	}
	myWorld->Step(1.0/60,8,1);
	for(b2Body *b = myWorld->GetBodyList(); b; b=b->GetNext())
	{    
        if (b->GetUserData() != NULL)
		{
			if(b->GetMass() > 1)
			{
				CCSprite *ballData = (CCSprite*)((Person *)b->GetUserData())->getSprite();
				ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
				ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
			else
			{
				CCSprite *ballData = (CCSprite*)((bullet *)b->GetUserData())->getSprite();
				ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
				ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
        }        
    }
	zmogus->movement();
}
void HelloWorld::BeginContact(b2Contact* contact)
{
	if(contact->GetFixtureA()->GetBody()->GetMass() < 1 && contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)
	{
		destroyBullet = contact->GetFixtureA()->GetBody();
		if(contact->GetFixtureB()->GetBody()->GetMass() > 1 && contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody && contact->GetFixtureB()->GetBody()->GetUserData() != zmogus)
		{
			hitBody = contact->GetFixtureB()->GetBody();
			hitPos = contact->GetFixtureA()->GetBody()->GetPosition();
		}
	}
	else if(contact->GetFixtureB()->GetBody()->GetMass() < 1 && contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody)
	{
		destroyBullet = contact->GetFixtureB()->GetBody();
		if(contact->GetFixtureA()->GetBody()->GetMass() > 1 && contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody && contact->GetFixtureA()->GetBody()->GetUserData() != zmogus)
		{
			hitBody = contact->GetFixtureA()->GetBody();
			hitPos = contact->GetFixtureB()->GetBody()->GetPosition();
		}
	}
}
void HelloWorld::deleteSprite(CCNode* sender)
{
  CCSprite *sprite = (CCSprite *)sender;
  this->removeChild(sprite, true);
}