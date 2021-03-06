#include "Player.h"

#include <2d/CCCamera.h>
#include <base/CCDirector.h>
#include <2d/CCLabel.h>

#include "Assets.h"
#include "Grid.h"
#include "StateManager.h"
#include "utility/Logger.h"
#include "input/MouseInput.h"
#include "gui/StatBox.h"

namespace entities {

	using namespace cocos2d;

	//private
	grid::GridNode* current_node;
	Vec2 dest;

	Camera* camera;

	std::vector<grid::GridNode*> neighbours;
	int hex_neighbours[] { 0, -1, 1, -1, -1, 0, 1, 0, 0, 1, 1, 1 };

	void select_neighbours(grid::GridNode* start_node) {
		for (int n = 0; n < sizeof(hex_neighbours) / sizeof(int); n += 2) {
			grid::GridNode* node = grid::get_neighbour(start_node, hex_neighbours[n], hex_neighbours[n + 1]);
			if (node && node->get_type() == grid::GRID_NODE_TYPE_FLOOR) {
				node->set_type(grid::GRID_NODE_TYPE_WALKABLE_FLOOR);
				neighbours.push_back(node);
			}
		}
		start_node->set_type(grid::GRID_NODE_TYPE_PLAYER_FLOOR);
	}

	void deselect_neighbours() {
		for (grid::GridNode* node : neighbours) {
			node->set_type(grid::GRID_NODE_TYPE_FLOOR);
		}
		neighbours.clear();

		current_node->set_type(grid::GRID_NODE_TYPE_FLOOR);
	}

	void walk_to(grid::GridNode* node) {
		dest.x = node->get_world_x() + (grid::HEX_SIZE - sprite->getContentSize().width) / 2;
		dest.y = node->get_world_y() + (grid::HEX_SIZE * .35f);

		select_neighbours(current_node);
	}

	//public
	Sprite* sprite;
	gui::StatBox* stat_box;

	void init_player() {
		sprite = Sprite::createWithTexture(assets::tex_char_warrior);
		sprite->setAnchorPoint(Vec2(0, 0));
		root::scene->addChild(sprite);

		stat_box = new gui::StatBox();

		current_node = grid::get_node(grid::grid_width / 2, grid::grid_height / 2);
		walk_to(current_node);

		Camera::getDefaultCamera()->setVisible(false);

		camera = Camera::createPerspective(60, (float)root::scene_size.width / root::scene_size.height, 1, 1000.0f);
		camera->setPositionZ(Director::getInstance()->getZEye() - 200);

		camera->setCameraFlag(CameraFlag::DEFAULT);
		camera->setCameraMask((unsigned short)CameraFlag::DEFAULT);
		root::scene->addChild(camera);
	}

	void update_player() {
		float camx = camera->getPositionX();
		float camy = camera->getPositionY();
		if (abs(sprite->getPositionX() - camx) <= 4.0f) camx = sprite->getPositionX();
		if (abs(sprite->getPositionY() - camy) <= 4.0f) camy = sprite->getPositionY();
		camx += (sprite->getPositionX() - camx) * .1f;
		camy += (sprite->getPositionY() - camy) * .1f;
		camera->setPositionX(camx);
		camera->setPositionY(camy);

		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);
		
		stat_box->box->setPosition(sprite->getPositionX(), sprite->getPositionY() + 64.0f);

		if (input::get_mouse_button_pressed(0)) {
			Vec2 mpos = input::get_mouse_pos();
			mpos.x += camera->getPositionX();
			mpos.y += camera->getPositionY();
			mpos.x -= root::scene_size.width / 2;
			mpos.y -= root::scene_size.height / 2;

			for (grid::GridNode* node : neighbours) {
				float dist = sqrt(pow((node->get_world_x() + (grid::HEX_WORLD_WIDTH * .5f)) - mpos.x, 2) + 
								  pow((node->get_world_y() + (grid::HEX_WORLD_HEIGHT * .5f)) - mpos.y, 2));

				if (dist <= grid::HEX_WORLD_WIDTH * .7f) {
					deselect_neighbours();

					current_node = node;
					walk_to(node);

					break;
				}
			}
		}
	}
};