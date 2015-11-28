#include "Player.h"

#include <2d/CCCamera.h>
#include <base/CCDirector.h>
#include <2d/CCLabel.h>

#include "Assets.h"
#include "map/Grid.h"
#include "map/TurnControl.h"
#include "entities/Enemy.h"
#include "StateManager.h"
#include "utility/Logger.h"
#include "input/MouseInput.h"
#include "gui/StatBox.h"

using namespace cocos2d;

namespace entities {

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

		walk_to(map::get_node(map::grid_width * .5f, map::grid_height * .5f));
	}

	void Player::update() {
		colour_flash.update();

		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);
		
		stat_box->box->setPosition(sprite->getPositionX(), sprite->getPositionY() + 64.0f);
	}

	void Player::take_dmg(float dmg) {
		stat_box->hp -= dmg;
		stat_box->set_hp(stat_box->hp);

		colour_flash.start(sprite, 1, .5f, 1, 0, 0);
	}

	void Player::on_node_clicked(map::GridNode* node) {
		for (map::GridNode* neighbour_node : neighbours) {
			if (node == neighbour_node) {
				if (!node->walkable) {
					for (int n = 0; n < entities::enemies.size(); ++n) {
						entities::Enemy* enemy = entities::enemies[n];

						if (enemy->current_node == node) {
							enemy->deal_dmg(entities::player->stat_box->dmg);

							break;
						}
					}
				}else {
					deselect_neighbours();

					walk_to(node);
				}

				break;
			}
		}
	}

	void Player::select_neighbours(map::GridNode* start_node) {
		for (int n = 0; n < sizeof(HEX_NEIGHBOURS) / sizeof(int); n += 2) {
			map::GridNode* node = map::get_neighbour(start_node, HEX_NEIGHBOURS[n], HEX_NEIGHBOURS[n + 1]);
			if (node) {
				neighbours.push_back(node);

				if (node->walkable && node->get_type() == map::GRID_NODE_TYPE_FLOOR) {
					node->set_type(map::GRID_NODE_TYPE_WALKABLE_FLOOR);
				}
			}
		}
	}

	void Player::deselect_neighbours() {
		for (map::GridNode* node : neighbours) {
			if (node->get_type() == map::GRID_NODE_TYPE_WALKABLE_FLOOR) {
				node->set_type(map::GRID_NODE_TYPE_FLOOR);
			}
		}
		neighbours.clear();

	}

	void Player::walk_to(map::GridNode* node) {
		if (current_node) {
			current_node->set_type(map::GRID_NODE_TYPE_FLOOR);
		}

		current_node = node;

		dest.x = node->get_world_x() + (map::HEX_SIZE - sprite->getContentSize().width) / 2;
		dest.y = node->get_world_y() + (map::HEX_SIZE * .35f);

		select_neighbours(current_node);
		current_node->set_type(map::GRID_NODE_TYPE_PLAYER_FLOOR);
	}
};