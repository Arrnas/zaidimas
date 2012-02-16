#include "Person.h"
USING_NS_CC;
Person::Person(string passName,
	int passX,int passY,
	int passHeight,int passWidth,
	int passWinh,int passWinw,
	HelloWorld * th,int layr,int chp,b2World *newWorld):name(passName),x(passX),y(passY),height(passHeight),
	width(passWidth),that(th),layer(layr),hp(chp)
{ 
	obj = CCSprite::spriteWithFile(name.c_str(),CCRectMake(0, 0, height,width) );      
    obj->setPosition( ccp(x,y) );
	that->addChild(obj,layer);

	_world = newWorld;
	// Create ball body and shape
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(x/PTM_RATIO, y/PTM_RATIO);
	ballBodyDef.userData = this;
	_body = _world->CreateBody(&ballBodyDef);
	 
	b2CircleShape circle;
	circle.m_radius = 26.0/PTM_RATIO;
	 
	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 1.0f;
	ballShapeDef.restitution = 0.1f;
	_body->CreateFixture(&ballShapeDef);
}