#ifndef __BULLET_H__
#define __BULLET_H__
#include "Box2D/Box2D.h"
#include "cocos2d.h"
USING_NS_CC;
#define PTM_RATIO 32.0
class HelloWorld;
class bullet
{ 
	b2Body * _body;
	CCSprite * _sprite;
	b2World *world;
	HelloWorld * that;
	int ID;
public:
	bullet(){}
	~bullet();
	bullet(string passName,
	int passX,int passY,
	HelloWorld * th,CCPoint point,b2World *_world,int id);
	CCSprite * getSprite(){ return _sprite; }
	int getId(){ return ID; }
};
#endif