#ifndef __USERINTERFACELAYER_H__
#define __USERINTERFACELAYER_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
class UserInterfaceLayer : public cocos2d::CCLayer
{
    public:
    virtual bool init();
	void changeup(int a){ a++; } 
    LAYER_NODE_FUNC(UserInterfaceLayer);
}; 
#endif // __USERINTERFACELAYER_H__