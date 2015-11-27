#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <2d/CCLayer.h>
#include <2d/CCScene.h>

namespace cc = cocos2d;

namespace root {

	class SceneInit : public cocos2d::LayerColor {

	public:
		static cocos2d::Scene* createScene();

		virtual bool init();
		virtual void update(float dt);

		void menuCloseCallback(cocos2d::Ref* pSender);

		CREATE_FUNC(SceneInit);

	private:
		bool inited_root = false;
	};
};

#endif
