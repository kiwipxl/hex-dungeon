#include "Enemy.h"

#include "Assets.h"
#include "Grid.h"
#include "StateManager.h"
#include "utility/Logger.h"
#include "input/MouseInput.h"
#include "gui/StatBox.h"

using namespace cocos2d;

namespace entities {

	//private
	std::vector<Enemy*> enemies;

	//public

	Enemy::Enemy() {
		sprite = Sprite::createWithTexture(assets::tex_char_skeleton);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setColor(Color3B(255, 120, 120));
		root::scene->addChild(sprite);

		stat_box = new gui::StatBox();

		current_node = grid::get_node((grid::grid_width / 2) + 4, grid::grid_height / 2);
		walk_to(current_node);
	}

	void Enemy::update() {
		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);

		stat_box->box->setPosition(sprite->getPositionX(), sprite->getPositionY() + 64.0f);
	}

	void Enemy::walk_to(grid::GridNode* node) {
		current_node->set_type(grid::GRID_NODE_TYPE_FLOOR);

		dest.x = node->get_world_x() + (grid::HEX_SIZE - sprite->getContentSize().width) / 2;
		dest.y = node->get_world_y() + (grid::HEX_SIZE * .35f);
		
		node->set_type(grid::GRID_NODE_TYPE_ENEMY_FLOOR);
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
		}
	}
};