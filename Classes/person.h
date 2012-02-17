#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
#include <math.h>
#include "Box2D/Box2D.h"
#include "cocos2d.h"

#define PTM_RATIO 32.0
using namespace std;
USING_NS_CC;
class HelloWorld;

class Person
{
private:
	bool shown1;
	CCLabelTTF *pLabel1;
	string fname;
	double x,y,height,width;
	int hp,layer;
	HelloWorld *that;
	b2World *_world;
	b2Body *_body;
	CCSprite *_ball;
	CCPoint moveTo;
public:
	Person():fname(""),x(0),y(0),width(0),height(0),layer(0),hp(0),that(NULL),_world(NULL),moveTo(0,0){}
	~Person(){}
	Person(string filename,double x,double y,double height,double width,int hp,int layer,HelloWorld *that,b2World *_world);
	CCSprite * getSprite(){ return _ball; }
	void move(CCPoint a);
	void movement();
	void rotateTo(CCPoint a);
};
#endif // __PERSON_H__