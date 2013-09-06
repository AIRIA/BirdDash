#include "GameMain.h"
#include "game/components/ShakeBird.h"
#include "base/BaseSprite.h"

enum
{
	kBirdBatchNode=2,
	kMenubg
};

bool GameMain::init()
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!BaseScene::init());
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/BGM/Main_bgm.mp3",true);
        setMainbg();
       
        res = true;
    }
    while (0);
    return res;
}

void GameMain::setMainbg()
{
    CCSprite *treeLeft = SPRITE_FRAME(main_trees_a@2x.png);
    CCSprite *treeRight = SPRITE_FRAME(main_trees_b@2x.png);
    CCSprite *sky = SPRITE_FRAME(main_bg_c@2x.png);
    CCSprite *grassDown = SPRITE_FRAME(main_bg_a@2x.png);
    CCSprite *grassUp = SPRITE_FRAME(main_bg_b@2x.png);
    CCSprite *menuBg = SPRITE_FRAME(main_menu_bg@2x.png);

    grassUp->setAnchorPoint(CCPointZero);
    grassDown->setAnchorPoint(CCPointZero);
    treeLeft->setAnchorPoint(ccp(0,1));
    treeRight->setAnchorPoint(ccp(1,1));
    treeLeft->setPosition(VisibleRect::leftTop());
    treeRight->setPosition(VisibleRect::rightTop());

    sky->setAnchorPoint(ccp(0.5f,1));
    sky->setPosition(VisibleRect::top());
    addChild(sky);

    //旋转的光芒
    CCSpriteBatchNode *lightBatchNode = CCSpriteBatchNode::createWithTexture(SPRITE_FRAME(main_bg_light@2x.png)->getTexture());
    ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
    lightBatchNode->setBlendFunc(cbl);
    for(int i=0; i<12; i++)
    {
        CCSprite *light = SPRITE_FRAME(main_bg_light@2x.png);
        light->setColor(ccWHITE);
        light->setScale(1.3f);
        light->setRotation(30*i);
        lightBatchNode->addChild(light);
    }
    addChild(lightBatchNode);
    lightBatchNode->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+50));
    lightBatchNode->runAction(CCRepeatForever::create(CCRotateBy::create(1.5f,30)));
    addChild(treeLeft);
    addChild(treeRight);
    grassUp->setPositionY(94);
    addChild(grassUp);
    menuBg->setAnchorPoint(ccp(1,0));
    menuBg->setRotation(-5);
    menuBg->setPosition(ccp(VisibleRect::right().x+10,94));
	addBirds();
    addChild(menuBg);
    addChild(grassDown);
    //title
    CCSprite *title = SPRITE_FRAME(main_title@2x.png);
    title->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-170));
    addChild(title);
    CCActionInterval *moveUp = CCMoveBy::create(1,ccp(0,10));
    title->runAction(CCRepeatForever::create(CCSequence::create(moveUp,moveUp->reverse(),NULL)));
}

void GameMain::loadAsset()
{
    frameCache->addSpriteFramesWithFile("images/main_menu/main_bg_a_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/main_menu/main_bg_b_RETINA.plist");
    frameCache->addSpriteFramesWithFile("images/main_menu/mainmenu_a_RETINA.plist");
}

void GameMain::addBirds()
{

    birdBatchNode = CCSpriteBatchNode::createWithTexture(SPRITE_FRAME(main_cha_blue@2x.png)->getTexture());
	setBird("main_cha_white@2x.png",ccp(170,620),ccp(0,5));
	setBird("main_cha_blue@2x.png",ccp(150,500),ccp(0,3));
	setBird("main_cha_pink@2x.png",ccp(190,400),ccp(0,2));
	setBird("main_cha_orange@2x.png",ccp(100,350),ccp(0,3));
	setBird("main_cha_green@2x.png",ccp(190,310),ccp(0,2));
	setBird("main_cha_red@2x.png",ccp(120,220),ccp(0,3));
	setBird("main_cha_purple@2x.png",ccp(230,200),ccp(0,0));
	setBird("main_cha_yellow@2x.png",ccp(550,80),ccp(0,0));
    addChild(birdBatchNode);

}

void GameMain::setBird( const char *birdName,CCPoint pos,CCPoint upDown )
{
	ShakeBird *bird = ShakeBird::createShakeBird(birdName);
	bird->setPosition(pos);
	CCActionInterval *moveUp = CCMoveBy::create(1,upDown);
	CCActionInterval *moveDown= CCMoveBy::create(1,ccp(0,-upDown.y));
	bird->runAction(CCRepeatForever::create(CCSequence::create(moveUp,moveUp->reverse(),moveDown,moveDown->reverse(),NULL)));
	birdBatchNode->addChild(bird);
}
