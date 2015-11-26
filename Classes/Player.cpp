#include "Player.h"

#include "Assets.h"
#include "Grid.h"
#include "StateManager.h"

namespace player {

	using namespace cocos2d;

	//private
	GridNode* current_node;
	Vec2 dest;

	void walk_to(GridNode* node) {
		dest.x = node->get_world_x();
		dest.y = node->get_world_y() + (grid::HEX_HEIGHT * .35f);
	}

	//public
	Sprite* sprite;

	void init() {
		sprite = Sprite::createWithTexture(assets::tex_char_warrior);
		sprite->setAnchorPoint(Vec2(0, 0));
		root::scene->addChild(sprite);
		
		current_node = grid::get_node(grid::grid_width / 2, grid::grid_height / 2);
		walk_to(current_node);

		highlight_neighbours();
	}

	void update() {
		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);
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