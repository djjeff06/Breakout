#include "EndWorld.h"
#include "Breakout.h"
#include <SimpleAudioEngine.h>

; USING_NS_CC;


Scene* EndWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = EndWorld::create();

	scene->addChild(layer);

	return scene;
}

bool EndWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto label = Label::createWithSystemFont("Game Over\n", "Arial", 64);
	label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	label->setPosition(Vec2(325, 300));
	this->addChild(label, 1);
	auto playlabel = Label::createWithSystemFont("Play Again?","Arial",64);
	playlabel->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	playlabel->setPosition(Vec2(325, 200));
	this->addChild(playlabel);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

		auto scene = Breakout::createScene();

		Director::getInstance()->replaceScene(scene);

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, playlabel);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/dearlybeloved.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/dearlybeloved.mp3", true);


	return true;
}