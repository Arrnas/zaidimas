#include "UserInterfaceLayer.h" 
#include "HelloWorldScene.h"

bool UserInterfaceLayer::init()
{
    bool bRet = false;
    do 
    {   // super init first        
        CC_BREAK_IF(! CCLayer::init());    

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();
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
	pCloseItem->setPosition( ccp(size.width-20,size.height-20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
	/////////////////////////////
	// 3. add a menu item with "||" image, which is clicked to pause the program
	//    you may modify it.

	// add a "pause" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pPauseItem = CCMenuItemImage::itemFromNormalImage(
										"PauseNormal.png",
										"PauseSelected.png",
										this,
										menu_selector(UserInterfaceLayer::menuPauseCallback));
	pPauseItem->setPosition( ccp(20,size.height-20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu1 = CCMenu::menuWithItems(pPauseItem, NULL);
	pMenu1->setPosition( CCPointZero );
	this->addChild(pMenu1, 1);



	// add a label shows "Hello World"
	// create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::labelWithString("Goodbye world", "Arial", 24);


	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height - 50) );

	// add the label as a child to this layer
	this->addChild(pLabel, 1);
	
	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::spriteWithFile("TrigerNormal.png");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(20, 20) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 1);


        bRet = true;
    } while (0);

    return bRet;
}
void UserInterfaceLayer::changeup(int c,int d)
{				
	string a;
	stringstream b;
	b << "pressed: " << c << "x: " << d;
	a = b.str();
	if(shown1)		
	{
		this->removeChild(pLabel1,1);
		pLabel1 = CCLabelTTF::labelWithString(a.c_str(), "Arial", 34);
		pLabel1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
		this->addChild(pLabel1,10);
	}
	else
	{
		pLabel1 = CCLabelTTF::labelWithString(a.c_str(), "Arial", 34);
		pLabel1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
		this->addChild(pLabel1,10);
		shown1 = true;
	}
} 
void UserInterfaceLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void UserInterfaceLayer::menuPauseCallback(CCObject* pSender)
{
	if(CCDirector::sharedDirector()->isPaused())
		CCDirector::sharedDirector()->resume();
	else
		CCDirector::sharedDirector()->pause();
}