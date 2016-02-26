#include "StartScene.h"
#include "Breakout.h"
#include <SimpleAudioEngine.h>

; USING_NS_CC;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("To Zanarkand.mp3", true);


	auto title = Label::createWithSystemFont("Breakout!", "Algerian", 80);
	title->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	title->setPosition(Vec2(325,400));
	this->addChild(title, 1);
	auto scoreLabel = Label::createWithSystemFont("Press any key to continue", "Algerian", 24);
	scoreLabel->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	scoreLabel->setPosition(Vec2(300, 300));
	this->addChild(scoreLabel,1);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [audio](EventKeyboard::KeyCode keyCode, Event* event) {

		auto scene = Breakout::createScene();
		//audio->stopBackgroundMusic();

		Director::getInstance()->replaceScene(scene);

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, title);

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/dearlybeloved.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/dearlybeloved.mp3", true);

	return true;
}