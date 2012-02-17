#include "UserInterfaceLayer.h" 
#include "HelloWorldScene.h"

bool UserInterfaceLayer::init()
{
    bool bRet = false;
    do 
    {   // super init first        
        CC_BREAK_IF(! CCLayer::init());    

    //todo, init stuff here
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(UserInterfaceLayer::menuCloseCallback));
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width-20,CCDirector::sharedDirector()->getWinSize().height-20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	// add a label shows "Hello World"
	// create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::labelWithString("Goodbye world", "Arial", 24);
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height - 50) );

	// add the label as a child to this layer
	this->addChild(pLabel, 1);



        bRet = true;
    } while (0);

    return bRet;
}
void UserInterfaceLayer::changeup(int c)
{				

} 
void UserInterfaceLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}