#include "Person.h"
#include "HelloWorldScene.h"

#define PTM_RATIO 32.0
#define SPEED_RATIO 10.0
USING_NS_CC;

Person::Person(string fname,
			   double x,double y,double height,double width,
			   int hp,int layer,
			   HelloWorld *that,
			   b2World *_world):fname(fname),
			   x(x),y(y),height(height),width(width),
			   hp(hp),layer(layer),
			   that(that),
			   _world(_world),
			   moveTo(x,600-y)
{
	_ball = CCSprite::spriteWithFile(fname.c_str(),CCRectMake(0, 0, width,height));
	_ball->setPosition(ccp(x,y));
	that->addChild(_ball,layer);

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
void Person::move(CCPoint a)
{ 
	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	moveTo = a;
	_body->SetLinearVelocity(b2Vec2(0,0));//stop the body to remove inertia
	_body->SetLinearVelocity(b2Vec2((a.x - currPos.x)/SPEED_RATIO,//click position - current position, screen height - click position (since the y axis is flipped, (0,0) is in the bottom left ) - current position = vector of the direction we want to go
									(size.height - a.y - currPos.y)/SPEED_RATIO));
}
void Person::movement()
{
	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if(b2Vec2((moveTo.x -currPos.x),//click position - current position, screen height - click position (since the y axis is flipped, (0,0) is in the bottom left ) - current position = vector of the direction we want to go
			(size.height - moveTo.y - currPos.y)) == b2Vec2(0,0))
	{
		moveTo = CCPoint(currPos.x,size.height - currPos.y);
		_body->SetLinearVelocity(b2Vec2(0,0));//stop the body
	}
	else
	{
		this->move(moveTo);
	}
}
void Person::rotateTo(CCPoint a)
{
	double angle=0;
	b2Vec2 currPos = _body->GetPosition();
	currPos *= PTM_RATIO;
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if((size.height - a.y - currPos.y) >= 0)
	{
		if((a.x - currPos.x) >= 0)
		{
			angle = CC_DEGREES_TO_RADIANS(0);
			angle += atan(abs(size.height - a.y - currPos.y)/abs( a.x - currPos.x));
		}
		else
		{
			angle = CC_DEGREES_TO_RADIANS(180);
			angle -= atan(abs(size.height - a.y - currPos.y)/abs( a.x - currPos.x));
		}
	}
	else
	{
		if((a.x - currPos.x) >= 0)
		{
			angle = CC_DEGREES_TO_RADIANS(360);
			angle -= atan(abs(size.height - a.y - currPos.y)/abs( a.x - currPos.x));
		}
		else
		{
			angle = CC_DEGREES_TO_RADIANS(180);
			angle += atan(abs(size.height - a.y - currPos.y)/abs( a.x - currPos.x));
		}
	}
	_body->SetTransform(_body->GetPosition(), angle);
}