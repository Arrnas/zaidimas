#ifndef __PERSON_H__
#define __PERSON_H__
#include <string>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#define PTM_RATIO 32.0

class HelloWorld;

class Person
{
	b2Body * _body;
	b2World *_world;
	int x,y,height,width,layer,hp;   //height,width - of the image
	string name;  //filename
	HelloWorld * that;     //pointer to the current scene object
	cocos2d::CCSprite *obj;      //image sprite
public:

	
	Person(){}
	Person(string passName,
	int passX,int passY,
	int passHeight,int passWidth,
	int passWinh,int passWinw,
	HelloWorld * th,int layr,int chp,b2World *newWorld);
	~Person(){}
	void setName(string passName){name = passName;}
	void setX(int passX){x = passX;}
	void setY(int passY){y= passY;}
	void setHeight(int passHeight){height = passHeight;}
	void setWidth(int passWidth){ width = passWidth;}
	void setThat(HelloWorld *th){that = th;}
	string getName(){return name;}
	HelloWorld * getThat(){return that;}
	cocos2d::CCSprite * getSprite(){return obj; }
	void remove(){that->removeChild(obj, true);}
	int getRealX(){return obj->getPosition().x;}
	int getRealY(){return obj->getPosition().y;}
	float getAngle(){ return obj->getRotation(); }
};
#endif