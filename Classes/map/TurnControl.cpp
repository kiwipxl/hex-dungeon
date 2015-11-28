#include "TurnControl.h"

#include <2d/CCCamera.h>
#include <base/CCDirector.h>

#include "Assets.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "gui/StatBox.h"
#include "input/MouseInput.h"
#include "map/Grid.h"
#include "StateManager.h"
#include "utility/Logger.h"

namespace map {

	using namespace cocos2d;

	//private
	Camera* camera;

	//public

	void init_turns() {
		Camera::getDefaultCamera()->setVisible(false);

		camera = Camera::createPerspective(60, (float)root::scene_size.width / root::scene_size.height, 1, 1000.0f);
		camera->setPositionZ(Director::getInstance()->getZEye());

		camera->setCameraFlag(CameraFlag::DEFAULT);
		camera->setCameraMask((unsigned short)CameraFlag::DEFAULT);
		root::scene->addChild(camera);
	}

	void update_turns() {
		//move camera
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

		//test if a node is being clicked on
		if (input::get_mouse_button_pressed(0)) {
			Vec2 mpos = input::get_mouse_pos();

			mpos.x += camera->getPositionX();
			mpos.y += camera->getPositionY();
			mpos.x -= root::scene_size.width / 2;
			mpos.y -= root::scene_size.height / 2;

			//find closest distance of each node to the mouse pos
			float closest_dist = FLT_MAX;
			GridNode* clicked_node = NULL;

			for (GridNode* node : grid_vec) {
				float dist = sqrt(pow((node->get_world_x() + (HEX_WORLD_WIDTH * .5f)) - mpos.x, 2) +
								  pow((node->get_world_y() + (HEX_WORLD_HEIGHT * .5f)) - mpos.y, 2));

				if (dist < closest_dist) {
					closest_dist = dist;
					clicked_node = node;
				}
			}

			if (closest_dist <= HEX_WORLD_WIDTH * .7f && clicked_node) {
				entities::player->on_node_clicked(clicked_node);
			}
		}
	}
};