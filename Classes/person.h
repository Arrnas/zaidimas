#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
#include <math.h>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "bullet.h"

#define PTM_RATIO 32.0
using namespace std;
USING_NS_CC;
class HelloWorld;

class Person
{
private:
	vector<bullet *> bulletArray;
	int bulletNumb;
	bool inAction;
	CCSpriteFrame *frame;
	CCAnimation *moveAnimation;
	CCAnimation *idleAnimation;
	CCAnimation *shootAnimation;
	CCSpriteBatchNode *batch;
	CCMutableArray<CCSpriteFrame *> *animFrames;
	CCMutableArray<CCSpriteFrame *> *idleFrames;
	CCMutableArray<CCSpriteFrame *> *shootingFrames;
	bool shown1;
	CCLabelTTF *pLabel1;
	string fname,atlasName;
	double x,y,height,width;
	int hp,layer;
	HelloWorld *that;
	b2World *_world;
	b2Body *_body;
	CCSprite *_ball;
	CCPoint moveTo;
	CCRepeat *shootRepeat;
	CCRepeatForever *idleRepeatForever;
	CCRepeatForever *moveRepeatForever;
	int currentAnimation;
public:
	Person():fname(""),x(0),y(0),width(0),height(0),layer(0),hp(0),that(NULL),_world(NULL),moveTo(0,0),atlasName(""){}
	~Person();
	Person(string filename,double x,double y,double height,double width,int hp,int layer,HelloWorld *that,b2World *_world,string atlasName);
	CCSprite * getSprite(){ return _ball; }
	void move(CCPoint a);
	void movement();
	void rotateTo(CCPoint a);
	double rotation(CCPoint a);
	void movingAnim();
	void idleAnim();
	void shootingAnim();
	void changeAnimation(int anim);
	void shoot(CCPoint direction);
	b2Body * getBody(){ return _body; }
	void deleteBullet(int numb){bulletArray.at(numb)->~bullet();}
	void hit(b2Vec2 pos);
	int getHP(){ return hp; }
};
#endif // __PERSON_H__