#include "SceneInit.h"

#include <base/CCDirector.h>

#include "StateManager.h"

using namespace cocos2d;

namespace root {

	Scene* SceneInit::createScene() {
		auto scene = Scene::create();
		auto layer = SceneInit::create();

		scene->addChild(layer);

		return scene;
	}

	bool SceneInit::init() {
		if (!LayerColor::initWithColor(Color4B(12, 12, 12, 255))) return false;

		this->scheduleUpdate();
		
		root::init_root(this);

		return true;
	}

	void SceneInit::update(float dt) {
		root::update_state(dt);
	}

	void SceneInit::menuCloseCallback(Ref* pSender) {
		Director::getInstance()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
		#endif
	}
};