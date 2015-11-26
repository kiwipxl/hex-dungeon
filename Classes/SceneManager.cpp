#include "SceneManager.h"

#include "Assets.h"
#include "Grid.h"
#include "Player.h"

using namespace cocos2d;

Scene* SceneManager::scene;
Size SceneManager::scene_size;

Scene* SceneManager::createScene()
{
    auto scene = Scene::create();
    auto layer = SceneManager::create();

    scene->addChild(layer);

    return scene;
}

bool SceneManager::init()
{
	if (!LayerColor::initWithColor(Color4B(12, 12, 12, 255))) return false;

	scene = (Scene*)this;
	scene_size = Director::getInstance()->getVisibleSize();

	assets::init();
	grid::init();
	player::init();

	this->scheduleUpdate();

    return true;
}

void SceneManager::update(float dt) {
	player::update();
}

void SceneManager::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
