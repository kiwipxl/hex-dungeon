#include "Player.h"

#include "SceneManager.h"
#include "Grid.h"
#include "Assets.h"

namespace player {

	using namespace cocos2d;

	//private
	GridNode* current_node;

	void move_to(Sprite* sprite, GridNode* node) {
		sprite->setPosition(node->get_world_x(), node->get_world_y() + (grid::HEX_HEIGHT * .35f));
	}

	//public

	void init() {
		auto char_warrior = Sprite::createWithTexture(assets::tex_char_warrior);
		char_warrior->setAnchorPoint(Vec2(0, 0));
		GridNode* player_node = grid::get_node(grid::grid_width / 2, grid::grid_height / 2);
		move_to(char_warrior, player_node);
		SceneManager::scene->addChild(char_warrior);
	}

	void highlight_neighbours() {
		int neighbours[]{ 0, -1, 1, -1, -1, 0, 1, 0, 0, 1, 1, 1 };

		for (int n = 0; n < sizeof(neighbours); n += 2) {
			GridNode* node = grid::get_node(
				current_node->get_grid_x() + neighbours[n], 
				current_node->get_grid_y() + neighbours[n + 1]);

			if (node) node->set_type(GRID_NODE_TYPE_WALKABLE_FLOOR);
		}
	}
};