#include "TurnControl.h"

#include <2d/CCCamera.h>
#include <base/CCDirector.h>

#include "Assets.h"
#include "StateManager.h"
#include "utility/Logger.h"
#include "input/MouseInput.h"
#include "entities/Player.h"

namespace map {

	using namespace cocos2d;

	//private
	Camera* camera;

	//public

	void init_turns() {
		Camera::getDefaultCamera()->setVisible(false);

		camera = Camera::createPerspective(60, (float)root::scene_size.width / root::scene_size.height, 1, 1000.0f);
		camera->setPositionZ(Director::getInstance()->getZEye() - 200);

		camera->setCameraFlag(CameraFlag::DEFAULT);
		camera->setCameraMask((unsigned short)CameraFlag::DEFAULT);
		root::scene->addChild(camera);
	}

	void update_turns() {
		float cam_destx = entities::player->sprite->getPositionX();
		float cam_desty = entities::player->sprite->getPositionY();

		float camx = camera->getPositionX();
		float camy = camera->getPositionY();
		if (abs(cam_destx - camx) <= 4.0f) camx = cam_destx;
		if (abs(cam_desty - camy) <= 4.0f) camy = cam_desty;
		camx += (cam_destx - camx) * .1f;
		camy += (cam_desty - camy) * .1f;
		camera->setPositionX(camx);
		camera->setPositionY(camy);
	}
};