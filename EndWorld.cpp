#include "EndWorld.h"
#include "Breakout.h"
#include <SimpleAudioEngine.h>

using namespace cocos2d;
using namespace std;


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

	int highscore = 0;
	FILE* fp = fopen("score.txt", "r");
	fscanf(fp, "%d", &highscore);
	fclose(fp);

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("To Zanarkand.mp3", true);

	auto label = Label::createWithSystemFont("Game Over\n", "Algerian", 64);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(Vec2(325, 420));
	this->addChild(label, 1);

	auto lbl_scorelbl = Label::createWithSystemFont("High Score: ", "Algerian", 64);
	lbl_scorelbl->setAnchorPoint(Vec2(0.5, 0.5));
	lbl_scorelbl ->setPosition(Vec2(290, 340));
	this->addChild(lbl_scorelbl);

	auto lbl_score = Label::createWithSystemFont(std::to_string(highscore), "Algerian", 64);
	lbl_score->setAnchorPoint(Vec2(0.5, 0.5));
	lbl_score->setPosition(Vec2(520,340));
	this->addChild(lbl_score);

	auto playlabel = Label::createWithSystemFont("Play Again?","Algerian",64);
	playlabel->setAnchorPoint(Vec2(0.5, 0.5));
	playlabel->setPosition(Vec2(325, 220));
	this->addChild(playlabel);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [audio](EventKeyboard::KeyCode keyCode, Event* event) {

		auto scene = Breakout::createScene();
		//audio->stopBackgroundMusic();

		Director::getInstance()->replaceScene(scene);

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, playlabel);

	return true;
}