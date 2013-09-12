#ifndef _ALIAS_H_
#define _ALIAS_H_


#define SHOW_EXIT_WIN "showexitwindow"
#define HIDE_EXIT_WIN "hideexitwindow"
#define RESUME_GAME "resume_game"
#define PP_ROW 9
#define PP_COL 7
#define BIRD_WRAPPER_WIDTH 526
#define BIRD_WRAPPER_HEIGHT 650
#define BOX_WIDTH (BIRD_WRAPPER_WIDTH/PP_COL)
#define BOX_HEIGHT 72
#define BOX_DOWN_TIME 0.1f


#define SPRITE(url) CCSprite::create(#url)
#define SPRITE_FRAME(URL) CCSprite::createWithSpriteFrameName(#URL)
#define CONFIG_GETBOOL CCUserDefault::sharedUserDefault()->getBoolForKey(#key,true);
#define CONFIG_GETSTR(key) CCUserDefault::sharedUserDefault()->getStringForKey(#key)
#define CONFIG_STRFORKEY(key,val) CCUserDefault::sharedUserDefault()->setStringForKey(#key,val)
#define CONFIG_BOOLFORKEY(key,val) CCUserDefault::sharedUserDefault()->setBoolForKey(#key,value)
#define CONFIG_ISEXITS CCUserDefault::sharedUserDefault()->isXMLFileExist()
#define CONFIG_CREATE CCUserDefault::sharedUserDefault()->

#endif // !_ALIAS_H_
