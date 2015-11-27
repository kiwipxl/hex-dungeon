#include "Player.h"

#include "Assets.h"
#include "Grid.h"
#include "StateManager.h"
#include "utility/Logger.h"
#include "input/MouseInput.h"

namespace player {

	using namespace cocos2d;

	//private
	GridNode* current_node;
	Vec2 dest;
	std::vector<GridNode*> neighbours;

	int hex_neighbours[] { 0, -1, 1, -1, -1, 0, 1, 0, 0, 1, 1, 1 };

	void select_neighbours(GridNode* start_node) {
		for (int n = 0; n < sizeof(hex_neighbours) / sizeof(int); n += 2) {
			GridNode* node = grid::get_neighbour(start_node, hex_neighbours[n], hex_neighbours[n + 1]);
			if (node && node->get_type() == GRID_NODE_TYPE_FLOOR) {
				node->set_type(GRID_NODE_TYPE_WALKABLE_FLOOR);
				neighbours.push_back(node);
			}
		}
	}

	void deselect_neighbours() {
		for (GridNode* node : neighbours) {
			node->set_type(GRID_NODE_TYPE_FLOOR);
		}
		neighbours.clear();
	}

	void walk_to(GridNode* node) {
		dest.x = node->get_world_x() + (grid::HEX_WIDTH - sprite->getContentSize().width) / 2;
		dest.y = node->get_world_y() + (grid::HEX_HEIGHT * .35f);

		select_neighbours(current_node);
	}

	//public
	Sprite* sprite;

	void init() {
		sprite = Sprite::createWithTexture(assets::tex_char_warrior);
		sprite->setAnchorPoint(Vec2(0, 0));
		root::scene->addChild(sprite);
		
		current_node = grid::get_node(grid::grid_width / 2, grid::grid_height / 2);
		walk_to(current_node);
	}

	void update() {
		sprite->setPositionX(sprite->getPositionX() + (dest.x - sprite->getPositionX()) * .25f);
		sprite->setPositionY(sprite->getPositionY() + (dest.y - sprite->getPositionY()) * .25f);

		//grid::set_camera_pos(sprite->getPositionX(), sprite->getPositionY());

		if (input::get_mouse_button_pressed(0)) {
			Vec2 mpos = input::get_mouse_pos();

			for (GridNode* node : neighbours) {
				Size size = node->get_sprite()->getContentSize();
				size.width *= node->get_sprite()->getScaleX();
				size.height *= node->get_sprite()->getScaleY();

				if (mpos.x >= node->get_world_x() && mpos.x <= node->get_world_x() + size.width &&
					mpos.y >= node->get_world_y() && mpos.y <= node->get_world_y() + size.height) {

					deselect_neighbours();

					current_node = node;
					walk_to(node);

					break;
				}
			}
		}
	}
};