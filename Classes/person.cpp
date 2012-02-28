#include "Person.h"
#include "HelloWorldScene.h"

#define PTM_RATIO 32.0
#define SPEED_RATIO 4.0
USING_NS_CC;

Person::Person(string fname,
			   double x,double y,double height,double width,
			   int hp,int layer,
			   HelloWorld *that,
			   b2World *_world,string atlasName):fname(fname),
			   x(x),y(y),height(height),width(width),
			   hp(hp),layer(layer),
			   that(that),
			   _world(_world),
			   moveTo(x,y),
			   inAction(false),
			   atlasName(atlasName),
			   bulletNumb(0)

{
	char pavadinimas[20];
	batch = CCSpriteBatchNode::batchNodeWithFile(atlasName.c_str());
	sprintf(pavadinimas,"%s%i.png",fname.c_str(),0);
	_ball = CCSprite::spriteWithSpriteFrameName(pavadinimas);
	_ball->setPosition(ccp(x,y));
	batch->addChild(_ball);
	that->addChild(batch,1);
	animFrames = new CCMutableArray<CCSpriteFrame *>;
	idleFrames = new CCMutableArray<CCSpriteFrame *>;
	shootingFrames = new CCMutableArray<CCSpriteFrame *>;
	for(int i = 0; i < 6; i++)
	{
		sprintf(pavadinimas,"%s%i.png",fname.c_str(),i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pavadinimas);
		animFrames->addObject(frame);
	}
	for(int i = 6; i < 9; i++)
	{
		sprintf(pavadinimas,"%s%i.png",fname.c_str(),i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pavadinimas);
		idleFrames->addObject(frame);
	}
	for(int i = 9;i<17;i++)
	{
		sprintf(pavadinimas,"%s%i.png",fname.c_str(),i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pavadinimas);
		shootingFrames->addObject(frame);
	}

	shootAnimation = CCAnimation::animationWithFrames(shootingFrames,0.08f);
	shootRepeat = CCRepeat::actionWithAction(CCAnimate::actionWithAnimation(shootAnimation,true),1);
	shootRepeat->retain();
	idleAnimation = CCAnimation::animationWithFrames(idleFrames,0.20f);
	idleRepeatForever = CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(idleAnimation,true));
	idleRepeatForever->retain();
	moveAnimation = CCAnimation::animationWithFrames(animFrames,0.20f);
	moveRepeatForever = CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(moveAnimation,true));
	moveRepeatForever->retain();
	// Create ball body and shape
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(x/PTM_RATIO,y/PTM_RATIO);
	ballBodyDef.userData = this;
	_body = _world->CreateBody(&ballBodyDef);
	 
	b2CircleShape circle;
	circle.m_radius = sqrt(width*width+height*height)/2.0/PTM_RATIO;//get the logest radius of a sprite
	 
	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.0f;
	_body->CreateFixture(&ballShapeDef);
}
void Person::shoot(CCPoint direction)
{
	double angle = this->rotation(direction);

	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	b2Vec2 bulletPos = currPos;
	bulletPos.x += x;
	bulletPos.y += y;
	double x = 122/2.0 * cos(angle)+currPos.x;
	double y = 122/2.0 * sin(angle)+currPos.y;
	bulletArray.push_back(new bullet("bullet.png",x,y,that,CCPoint(direction.x - currPos.x,direction.y - currPos.y),_world,bulletNumb));
	bulletNumb++;
}
void Person::move(CCPoint a)
{ 
	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	moveTo = a;
	_body->SetLinearVelocity(b2Vec2(0,0));//stop the body to remove inertia
	_body->ApplyLinearImpulse(b2Vec2((a.x - currPos.x)/SPEED_RATIO,
		(a.y - currPos.y)/SPEED_RATIO),_body->GetPosition());
}
void Person::movement()
{
	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(abs(moveTo.x -currPos.x) < 10
			 && abs(moveTo.y - currPos.y) < 10)
	{
		moveTo = CCPoint(currPos.x,currPos.y);
		_body->SetLinearVelocity(b2Vec2(0,0));//stop the body
		_body->SetAngularVelocity(0.0f);
		this->changeAnimation(0);
	}
	else
	{
		this->move(moveTo);
		this->changeAnimation(1);
	}
}
double Person::rotation(CCPoint a)
{
	double angle=0;
	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if((a.y - currPos.y) >= 0)
	{
		if((a.x - currPos.x) >= 0)
		{
			angle = CC_DEGREES_TO_RADIANS(0);
			angle += atan(abs(a.y - currPos.y)/abs( a.x - currPos.x));
		}
		else
		{
			angle = CC_DEGREES_TO_RADIANS(180);
			angle -= atan(abs(a.y - currPos.y)/abs( a.x - currPos.x));
		}
	}
	else
	{
		if((a.x - currPos.x) >= 0)
		{
			angle = CC_DEGREES_TO_RADIANS(360);
			angle -= atan(abs(a.y - currPos.y)/abs( a.x - currPos.x));
		}
		else
		{
			angle = CC_DEGREES_TO_RADIANS(180);
			angle += atan(abs(a.y - currPos.y)/abs( a.x - currPos.x));
		}
	}
	return angle;
}
void Person::rotateTo(CCPoint a)
{
	_body->SetTransform(_body->GetPosition(), this->rotation(a));
}
void Person::movingAnim()
{
	_ball->stopAllActions();
	_ball->runAction(moveRepeatForever);
	inAction = true;
}
void Person::idleAnim()
{
	_ball->stopAllActions();
	_ball->runAction(idleRepeatForever);
	inAction = false;
}
void Person::shootingAnim()
{
	_ball->stopAllActions();
	_ball->runAction(shootRepeat);
}
Person::~Person()
{ 
	delete animFrames; 
	delete idleFrames;
	delete shootingFrames;
	_body->SetUserData(NULL);
	that->removeChild(batch,true);
	_world->DestroyBody(_body);
}
void Person::changeAnimation(int anim)//0-idle,1-run,2-shoot
{
	if(anim == 0)
	{
		if(shootRepeat->isDone() && currentAnimation != 0)
		{
			this->idleAnim();
			currentAnimation = 0;
		}
	}
	else if(anim == 1 && currentAnimation != 1)
	{
		if(shootRepeat->isDone())
		{
			this->movingAnim();
			currentAnimation = 1;
		}
	}
	else if(anim == 2)
	{
		this->shootingAnim();
		currentAnimation = 2;
	}
}
void Person::hit(b2Vec2 pos)
{
	CCSprite *hitSprite = CCSprite::spriteWithSpriteFrameName("hit.png");
	pos*=PTM_RATIO;
	hitSprite->setPosition(ccp(pos.x,pos.y));
	that->addChild(hitSprite,3);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(that,callfuncN_selector(HelloWorld::deleteSprite));
	CCFiniteTimeAction* delay = CCDelayTime::actionWithDuration((ccTime)0.1);
	hitSprite->runAction(CCSequence::actions(delay,actionMoveDone,NULL));
	hp--; 
}