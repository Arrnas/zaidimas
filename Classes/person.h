#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
#include <math.h>
#include "Box2D/Box2D.h"
#include "cocos2d.h"


using namespace std;
USING_NS_CC;
class HelloWorld;

class Person
{
private:
	string fname;
	double x,y,height,width;
	int hp,layer;
	HelloWorld *that;
	b2World *_world;
	b2Body *_body;
	CCSprite *_ball;
public:
	Person():fname(""),x(0),y(0),width(0),height(0),layer(0),hp(0),that(NULL),_world(NULL){}
	~Person(){}
	Person(string filename,double x,double y,double height,double width,int hp,int layer,HelloWorld *that,b2World *_world);
	CCSprite * getSprite(){ return _ball; }
};
#endif // __PERSON_H__