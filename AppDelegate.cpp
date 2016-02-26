/*************************************************************
Author: Jefferson Dionisio
Last Edit: February 10, 2016
Title: Snake Speed

Credits:
Music: Kyle Landry - Kingdom Hearts - Dearly Beloved (cover)

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
		glview = GLViewImpl::create("Hello World");
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