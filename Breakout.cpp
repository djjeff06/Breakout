#include "Breakout.h"
#include "EndWorld.h"

using namespace cocos2d;
using namespace std;

static boolean check,start;
static int currentscore,life,bricks;

Scene* Breakout::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Breakout::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

bool Breakout::init() {


	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	start = false;
	check = true;
	life = 2;
	currentscore = 0;
	bricks = 112;

	auto lbl_scorelbl = Label::createWithSystemFont("Score: ", "arial", 32);
	lbl_scorelbl->setAnchorPoint(Vec2(0.5, 0.5));
	lbl_scorelbl->setPosition(520, 600);
	this->addChild(lbl_scorelbl , 2);

	auto lbl_score = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
	lbl_score->setAnchorPoint(Vec2(0.5, 0.5));
	lbl_score->setPosition(580,600);
	this->addChild(lbl_score, 2);

	auto lbl_lifelbl = Label::createWithSystemFont("Life: ", "arial", 32);
	lbl_lifelbl->setAnchorPoint(Vec2(0.5, 0.5));
	lbl_lifelbl->setPosition(90, 600);
	this->addChild(lbl_lifelbl, 2);

	auto lbl_life = Label::createWithSystemFont(std::to_string(life), "arial", 32);
	lbl_life->setAnchorPoint(Vec2(0.5, 0.5));
	lbl_life->setPosition(140, 600);
	this->addChild(lbl_life, 2);

	auto prompt = Label::createWithSystemFont("Press Spacebar to deploy a ball!", "arial", 16);
	prompt->setAnchorPoint(Vec2(0.5, 0.5));
	prompt->setPosition(300, 600);
	this->addChild(prompt);
	
	auto platform = Sprite::create("platform.jpg");
	platform->setPosition(320, 70);
	auto pb_platform = PhysicsBody::createBox(platform->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	pb_platform->setDynamic(false);
	pb_platform->setCollisionBitmask(1);
	pb_platform->setContactTestBitmask(true);
	platform->setPhysicsBody(pb_platform);
	this->addChild(platform,1);

	auto v_wall1 = Sprite::create("vertical_wall.jpg");
	v_wall1->setPosition(25, 320);
	auto pb_wall1 = PhysicsBody::createBox(v_wall1->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	pb_wall1->setDynamic(false);
	v_wall1->setPhysicsBody(pb_wall1);
	this->addChild(v_wall1, 1);

	auto v_wall2 = Sprite::create("vertical_wall.jpg");
	v_wall2->setPosition(615, 320);
	auto pb_wall2 = PhysicsBody::createBox(v_wall2->getContentSize(),PhysicsMaterial(0.0f,1.0f,0.0f));
	pb_wall2->setDynamic(false);
	v_wall2->setPhysicsBody(pb_wall2);
	this->addChild(v_wall2, 1);

	auto h_wall = Sprite::create("horizontal_wall.jpg");
	h_wall->setPosition(320, 580);
	auto pb_wall3 = PhysicsBody::createBox(h_wall->getContentSize(),PhysicsMaterial(1.0f,1.0f,1.0f));
	pb_wall3->setDynamic(false);
	h_wall->setPhysicsBody(pb_wall3);
	this->addChild(h_wall, 1);

	std::shared_ptr<Vector<Sprite*>>  yellowbrick1 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  yellowbrick2 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  greenbrick1 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  greenbrick2 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  orangebrick1 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  orangebrick2 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  redbrick1 = std::make_shared<Vector<Sprite*>>();
	std::shared_ptr<Vector<Sprite*>>  redbrick2 = std::make_shared<Vector<Sprite*>>();

	std::shared_ptr<Vector<PhysicsBody*>>  phyellow1 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phyellow2 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phgreen1 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phgreen2 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phorange1 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phorange2 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phred1 = std::make_shared<Vector<PhysicsBody*>>();
	std::shared_ptr<Vector<PhysicsBody*>>  phred2 = std::make_shared<Vector<PhysicsBody*>>();

	//initialize bricks
	for (int i = 0; i < 14; i++) {

		yellowbrick1->pushBack(Sprite::create("yellow_brick.jpg"));
		yellowbrick1->at(i)->setPosition(Vec2(60+(40*i), 450));
		phyellow1->pushBack(PhysicsBody::createBox(yellowbrick1->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phyellow1->at(i)->setDynamic(false);
		yellowbrick1->at(i)->setPhysicsBody(phyellow1->at(i));
		this->addChild(yellowbrick1->at(i));
		yellowbrick2->pushBack(Sprite::create("yellow_brick.jpg"));
		yellowbrick2->at(i)->setPosition(Vec2(60 + (40 * i), 464));
		phyellow2->pushBack(PhysicsBody::createBox(yellowbrick2->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phyellow2->at(i)->setDynamic(false);
		yellowbrick2->at(i)->setPhysicsBody(phyellow2->at(i));
		this->addChild(yellowbrick2->at(i));

		greenbrick1->pushBack(Sprite::create("green_brick.jpg"));
		greenbrick1->at(i)->setPosition(Vec2(60 + (40 * i), 478));
		phgreen1->pushBack(PhysicsBody::createBox(greenbrick1->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phgreen1->at(i)->setDynamic(false);
		greenbrick1->at(i)->setPhysicsBody(phgreen1->at(i));
		this->addChild(greenbrick1->at(i));
		greenbrick2->pushBack(Sprite::create("green_brick.jpg"));
		greenbrick2->at(i)->setPosition(Vec2(60 + (40 * i), 492));
		phgreen2->pushBack(PhysicsBody::createBox(greenbrick2->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phgreen2->at(i)->setDynamic(false);
		greenbrick2->at(i)->setPhysicsBody(phgreen2->at(i));
		this->addChild(greenbrick2->at(i));

		orangebrick1->pushBack(Sprite::create("orange_brick.jpg"));
		orangebrick1->at(i)->setPosition(Vec2(60 + (40 * i), 506));
		phorange1->pushBack(PhysicsBody::createBox(orangebrick1->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phorange1->at(i)->setDynamic(false);
		orangebrick1->at(i)->setPhysicsBody(phorange1->at(i));
		this->addChild(orangebrick1->at(i));
		orangebrick2->pushBack(Sprite::create("orange_brick.jpg"));
		orangebrick2->at(i)->setPosition(Vec2(60 + (40 * i), 520));
		phorange2->pushBack(PhysicsBody::createBox(orangebrick2->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phorange2->at(i)->setDynamic(false);
		orangebrick2->at(i)->setPhysicsBody(phorange2->at(i));
		this->addChild(orangebrick2->at(i));

		redbrick1->pushBack(Sprite::create("red_brick.jpg"));
		redbrick1->at(i)->setPosition(Vec2(60 + (40 * i), 534));
		phred1->pushBack(PhysicsBody::createBox(redbrick1->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phred1->at(i)->setDynamic(false);
		redbrick1->at(i)->setPhysicsBody(phred1->at(i));
		this->addChild(redbrick1->at(i));
		redbrick2->pushBack(Sprite::create("red_brick.jpg"));
		redbrick2->at(i)->setPosition(Vec2(60 + (40 * i), 548));
		phred2->pushBack(PhysicsBody::createBox(redbrick2->at(i)->getContentSize(), PhysicsMaterial(0, 1, 0)));
		phred2->at(i)->setDynamic(false);
		redbrick2->at(i)->setPhysicsBody(phred2->at(i));
		this->addChild(redbrick2->at(i));

	}

	auto eventListener = EventListenerKeyboard::create();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Breakout::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	eventListener->onKeyPressed = [platform,yellowbrick1,yellowbrick2,greenbrick1,greenbrick2,orangebrick1,orangebrick2,redbrick1,redbrick2,lbl_score,lbl_life,this](EventKeyboard::KeyCode keyCode, Event* event) {

		Vec2 loc = event->getCurrentTarget()->getPosition();

		switch (keyCode) {

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			auto moveBy = MoveBy::create(0.2, Point(-40, 0));
			platform->runAction(moveBy);
			break;
		}

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			auto moveBy = MoveBy::create(0.2, Point(40, 0));
			platform->runAction(moveBy);
			break;
		}

		case EventKeyboard::KeyCode::KEY_SPACE:
		{

			if (start == false) {

					auto ball = Sprite::create("ball.png");
					ball->setPosition(150, 400);
					auto pb_ball = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0.1f, 1.0f, 0.0f));
					pb_ball->setDynamic(true);
					//pb_ball->setLinearDamping(0.0);
					pb_ball->setVelocity(Vec2(100, -150));
					pb_ball->setCollisionBitmask(2);
					pb_ball->setContactTestBitmask(true);
					ball->setPhysicsBody(pb_ball);
					this->addChild(ball, 1);
					this->removeChild(lbl_life);
					auto lbl_life = Label::createWithSystemFont(std::to_string(life), "arial", 32);
					lbl_life->setAnchorPoint(Vec2(0.5, 0.5));
					lbl_life->setPosition(140, 600);
					this->addChild(lbl_life, 2);
					start = true;

				auto removeBrick = CallFunc::create([yellowbrick1,yellowbrick2,greenbrick1,greenbrick2,orangebrick1,orangebrick2,redbrick1,redbrick2,ball,lbl_score,this]() {

					float distance;

					for (int i = 0; i < 14; i++) {

						distance = powf(yellowbrick1->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(yellowbrick1->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check ==true) {

							yellowbrick1->at(i)->setPosition(580, 600);
							this->removeChild(yellowbrick1->at(i));
							currentscore++;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}
						
						distance = powf(yellowbrick2->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(yellowbrick2->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check==true) {

							yellowbrick2->at(i)->setPosition(580, 600);
							this->removeChild(yellowbrick2->at(i));
							currentscore++;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

						distance = powf(greenbrick1->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(greenbrick1->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check==true) {

							greenbrick1->at(i)->setPosition(580, 600);
							this->removeChild(greenbrick1->at(i));
							currentscore += 3;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

						distance = powf(greenbrick2->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(greenbrick2->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check==true) {

							greenbrick2->at(i)->setPosition(580, 600);
							this->removeChild(greenbrick2->at(i));
							currentscore += 3;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

						distance = powf(orangebrick1->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(orangebrick1->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check==true) {

							orangebrick1->at(i)->setPosition(580, 600);
							this->removeChild(orangebrick1->at(i));
							currentscore += 5;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

						distance = powf(orangebrick2->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(orangebrick2->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check==true) {

							orangebrick2->at(i)->setPosition(580, 600);
							this->removeChild(orangebrick2->at(i));
							currentscore += 5;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

						distance = powf(redbrick1->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(redbrick1->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check==true) {

							redbrick1->at(i)->setPosition(580, 600);
							this->removeChild(redbrick1->at(i));
							currentscore += 5;
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

						distance = powf(redbrick2->at(i)->getPositionX() - ball->getPositionX(), 2) + powf(redbrick2->at(i)->getPositionY() - ball->getPositionY(), 2);
						distance = sqrt(distance);
						if (distance <= 25 && check ==true) {

							redbrick2->at(i)->setPosition(580, 600);
							this->removeChild(redbrick2->at(i));
							check = false;

							this->removeChild(lbl_score);
							auto label = Label::createWithSystemFont(std::to_string(currentscore), "arial", 32);
							label->setAnchorPoint(Vec2(0.5, 0.5));
							label->setPosition(580, 600);
							this->addChild(label, 2);
							bricks--;

						}

					}

				});

				auto lifeDecrease = CallFunc::create([ball,lbl_life,this]() {

					if (ball->getPositionY() < 0 &&	start == true) {

						life--;
						start = false;

						if (life < -1 || bricks == 0) {

							auto scene = EndWorld::createScene();
							this->removeChild(lbl_life);
							int storage = 0;
							FILE *fp;
							fp = fopen("score.txt","r");
							fscanf(fp,"%d",&storage);
							fclose(fp);
							if (currentscore > storage) {

								fp = fopen("score.txt", "w");
								fprintf(fp, "%d", currentscore);
								fclose(fp);

							}

							Director::getInstance()->replaceScene(scene);

						}

					}
						

				});

				auto seq = Sequence::create(removeBrick, lifeDecrease,nullptr);
				auto repeat = RepeatForever::create(seq);
				this->runAction(repeat);

			}

		}

		}

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,platform);

	return true;

}

bool Breakout::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	// check if the bodies have collided
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{


		

		check = true;

		CCLOG("COLLISION HAS OCCURED");

	}

	return true;
}