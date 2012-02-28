#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "userInterfaceLayer.h"
#include "Box2D/Box2D.h"
#include "Person.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer,public b2ContactListener
{
	UserInterfaceLayer *userInterfaceLayer;
	b2World *myWorld;
	b2Body *_body;
	CCSprite *_ball;
	Person *zmogus,*enemy;
	CCTouch* finger;
	b2Body *destroyBullet;
	b2Body *hitBody;
	b2Vec2 hitPos;
	int score;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void tick(cocos2d::ccTime dt);
	void tock(cocos2d::ccTime dt);
	void BeginContact(b2Contact* contact);
	void deleteSprite(CCNode* sender);
	~HelloWorld(){	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames(); }
};

#endif // __HELLOWORLD_SCENE_H__
