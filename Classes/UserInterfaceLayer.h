#ifndef __USERINTERFACELAYER_H__
#define __USERINTERFACELAYER_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include <string>
#include <sstream>
USING_NS_CC;
using namespace std;
class UserInterfaceLayer : public cocos2d::CCLayer
{
	bool shown1;
	CCLabelTTF *pLabel1;
    public:
    virtual bool init();
	void changeup(int c);
    LAYER_NODE_FUNC(UserInterfaceLayer);
}; 
#endif // __USERINTERFACELAYER_H__