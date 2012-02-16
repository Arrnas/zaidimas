#include "UserInterfaceLayer.h" 
USING_NS_CC;
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