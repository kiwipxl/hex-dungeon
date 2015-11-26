#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "cocos2d.h"

class SceneManager : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* scene;
	static cocos2d::Size scene_size;

    virtual bool init();
	virtual void update(float dt);
    
	void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(SceneManager);
};

#endif // __HELLOWORLD_SCENE_H__
