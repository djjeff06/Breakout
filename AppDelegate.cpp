/*************************************************************
Author: Jefferson Dionisio
Last Edit: February 27, 2016
Game: Breakout

Credits: Arcade Bloop Sound Effect - https://www.youtube.com/watch?v=cDcG9V-C5i4
		 Nobuo Uematsu - To Zanarkand - https://www.youtube.com/watch?v=AgCrwvHPw-M
		 Nobuo Uematsu - Besaid Island - https://www.youtube.com/watch?v=XG93NDv96os
**************************************************************/

#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Breakout");
		glview->setFrameSize(640, 640);
		director->setOpenGLView(glview);
	}

	auto scene = StartScene::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}