#include "UserInterfaceLayer.h" 

bool UserInterfaceLayer::init()
{
    bool bRet = false;
    do 
    {   // super init first        
        CC_BREAK_IF(! CCLayer::init());    

    //todo, init stuff here

        bRet = true;
    } while (0);

    return bRet;
}
void UserInterfaceLayer::changeup(int c)
{				
	string a;
	stringstream b;
	b << "x: " << c;
	a = b.str();
	if(shown1)		
	{
		this->removeChild(pLabel1,1);
		pLabel1 = CCLabelTTF::labelWithString(a.c_str(), "Arial", 34);
		pLabel1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
		this->addChild(pLabel1,1);
	}
	else
	{
		pLabel1 = CCLabelTTF::labelWithString(a.c_str(), "Arial", 34);
		pLabel1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
		this->addChild(pLabel1,1);
		shown1 = true;
	}
} 