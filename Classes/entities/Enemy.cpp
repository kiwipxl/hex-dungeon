#include "Enemy.h"

#include "Assets.h"

#include "entities/Player.h"

#include "gui/StatBox.h"

#include "input/MouseInput.h"

#include "map/Grid.h"

#include "StateManager.h"

#include "utility/Logger.h"
#include "utility/Misc.h"

using namespace cocos2d;

namespace entities {

	//private

	//public
	std::vector<Enemy*> enemies;

	Enemy::Enemy() {
		sprite = Sprite::createWithTexture(assets::tex_char_skeleton);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setColor(Color3B(255, 120, 120));
		root::scene->addChild(sprite);

		stat_box = new gui::StatBox(8 + (rand() % 4), 2 + (rand() % 7));

		while (true) {
			int gridx = rand() % map::grid_width;
			int gridy = rand() % map::grid_height;

			map::GridNode* node = map::get_node(gridx, gridy);
			if (node && node->walkable) {
				walk_to(node);
				break;
			}
		}
	}

	void Enemy::remove() {
		stat_box->remove();
		root::scene->removeChild(sprite);

		if (current_node) {
			current_node->set_type(map::GRID_NODE_TYPE_FLOOR);
		}
	}

	void Enemy::update() {
		colour_flash.update();

		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);

		stat_box->box->setPosition(sprite->getPositionX(), sprite->getPositionY() + 64.0f);
	}

	void Enemy::walk_to(map::GridNode* node) {
		if (current_node) {
			current_node->set_type(map::GRID_NODE_TYPE_FLOOR);
		}

		current_node = node;

		dest.x = node->get_world_x() + (map::HEX_SIZE - sprite->getContentSize().width) / 2;
		dest.y = node->get_world_y() + (map::HEX_SIZE * .35f);

		node->set_type(map::GRID_NODE_TYPE_ENEMY_FLOOR);
	}

	void Enemy::deal_dmg(float dmg) {
		stat_box->hp -= dmg;
		stat_box->set_hp(stat_box->hp);

		colour_flash.start(sprite, 1, .25f, 2, 0, 0);
		utility::shake_screen(.2f, 7.0f);

		if (stat_box->hp <= 0) {
			removal_scheduled = true;
		}
	}

	/* ================================================================= */

	Enemy* create_enemy() {
		Enemy* enemy = new Enemy();
		enemies.push_back(enemy);

		return enemy;
	}

	void update_enemies() {
		for (int n = 0; n < enemies.size(); ++n) {
			enemies[n]->update();

			if (enemies[n]->is_removal_scheduled()) {
				enemies[n]->remove();

				enemies.erase(enemies.begin() + n);
				--n;
			}
		}
		entities::player->refresh_neighbours();
	}
};