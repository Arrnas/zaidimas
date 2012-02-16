#include "Person.h"
#include "HelloWorldScene.h"

#define PTM_RATIO 32.0
USING_NS_CC;

Person::Person(string fname,
			   double x,double y,double height,double width,
			   int hp,int layer,
			   HelloWorld *that,
			   b2World *_world):fname(fname),
			   x(x),y(y),height(height),width(width),
			   hp(hp),layer(layer),
			   that(that),
			   _world(_world)
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
	ballShapeDef.restitution = 1.0f;
	_body->CreateFixture(&ballShapeDef);
}