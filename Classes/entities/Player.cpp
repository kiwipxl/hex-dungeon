#include "Player.h"

#include <2d/CCCamera.h>
#include <base/CCDirector.h>
#include <2d/CCLabel.h>

#include "Assets.h"
#include "map/Grid.h"
#include "map/TurnControl.h"
#include "StateManager.h"
#include "utility/Logger.h"
#include "input/MouseInput.h"
#include "gui/StatBox.h"

namespace entities {

	using namespace cocos2d;

	//private static
	const int HEX_NEIGHBOURS[]{ 0, -1, 1, -1, -1, 0, 1, 0, 0, 1, 1, 1 };

	//public
	Player* player;

	void init_player() {
		player = new Player();
	}

	Player::Player() {
		sprite = Sprite::createWithTexture(assets::tex_char_warrior);
		sprite->setAnchorPoint(Vec2(0, 0));
		root::scene->addChild(sprite);

		stat_box = new gui::StatBox(25, 4);

		current_node = map::get_node(map::grid_width / 2, map::grid_height / 2);
		walk_to(current_node);
	}

	void Player::update() {
		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);
		
		stat_box->box->setPosition(sprite->getPositionX(), sprite->getPositionY() + 64.0f);

		if (input::get_mouse_button_pressed(0)) {
			Vec2 mpos = input::get_mouse_pos();
			mpos.x += map::camera->getPositionX();
			mpos.y += map::camera->getPositionY();
			mpos.x -= root::scene_size.width / 2;
			mpos.y -= root::scene_size.height / 2;

			for (map::GridNode* node : neighbours) {
				float dist = sqrt(pow((node->get_world_x() + (map::HEX_WORLD_WIDTH * .5f)) - mpos.x, 2) + 
								  pow((node->get_world_y() + (map::HEX_WORLD_HEIGHT * .5f)) - mpos.y, 2));

				if (dist <= map::HEX_WORLD_WIDTH * .7f) {
					deselect_neighbours();

					current_node = node;
					walk_to(node);

					break;
				}
			}
		}
	}

	void Player::select_neighbours(map::GridNode* start_node) {
		for (int n = 0; n < sizeof(HEX_NEIGHBOURS) / sizeof(int); n += 2) {
			map::GridNode* node = map::get_neighbour(start_node, HEX_NEIGHBOURS[n], HEX_NEIGHBOURS[n + 1]);
			if (node && node->get_type() == map::GRID_NODE_TYPE_FLOOR) {
				node->set_type(map::GRID_NODE_TYPE_WALKABLE_FLOOR);
				neighbours.push_back(node);
			}
		}
		start_node->set_type(map::GRID_NODE_TYPE_PLAYER_FLOOR);
	}

	void Player::deselect_neighbours() {
		for (map::GridNode* node : neighbours) {
			node->set_type(map::GRID_NODE_TYPE_FLOOR);
		}
		neighbours.clear();

		current_node->set_type(map::GRID_NODE_TYPE_FLOOR);
	}

	void Player::walk_to(map::GridNode* node) {
		dest.x = node->get_world_x() + (map::HEX_SIZE - sprite->getContentSize().width) / 2;
		dest.y = node->get_world_y() + (map::HEX_SIZE * .35f);

		select_neighbours(current_node);
	}
};