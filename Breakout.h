#pragma once

#include "cocos2d.h"

class Breakout : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Breakout);

private:
	cocos2d::PhysicsWorld *sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	bool Breakout::onContactBegin(cocos2d::PhysicsContact &contact);
};
