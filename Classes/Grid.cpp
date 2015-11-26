#include "Grid.h"

#include "Assets.h"
#include "StateManager.h"
#include "input/MouseInput.h"
#include "utility/Logger.h"

namespace grid {

	using namespace cocos2d;

	//public
	std::vector<GridNode*> grid_vec;
	int grid_width;
	int grid_height;
	float map_width;
	float map_height;

	Node* node_container;
	GridNode* last_clicked_node;

	void init() {
		node_container = Sprite::create();
		root::scene->addChild(node_container, 0);

		grid_width = root::scene_size.width / HEX_WORLD_WIDTH;
		grid_height = root::scene_size.height / HEX_WORLD_HEIGHT;
		grid_width *= 1.5f;
		grid_height *= 1.5f;
		map_width = grid_width * HEX_WORLD_WIDTH;
		map_height = grid_height * HEX_WORLD_HEIGHT;

		set_camera_pos(root::scene_size.width / 2.0f, root::scene_size.height / 2.0f);

		for (int y = 0; y < grid_height; ++y) {
			for (int x = 0; x < grid_width; ++x) {
				GridNodeType type = GRID_NODE_TYPE_FLOOR;
				if (rand() / (float)RAND_MAX >= .8f) type = GRID_NODE_TYPE_WALL;

				auto hex = Sprite::create();
				node_container->addChild(hex, 0);

				hex->setAnchorPoint(Vec2(0, 0));
				hex->setPosition((x + ((y % 2) * .5f)) * HEX_WORLD_WIDTH, y * HEX_WORLD_HEIGHT);

				GridNode* node = new GridNode(
					x, y, 
					hex->getPositionX() + node_container->getPositionX(), 
					hex->getPositionY() + node_container->getPositionY(), 
					hex, type);

				node->update_texture();
				
				grid_vec.push_back(node);
			}
		}
	}

	void set_camera_pos(float x, float y) {
		node_container->setPosition((root::scene_size.width - map_width) / 2 + (root::scene_size.width / 2 - x), 
									(root::scene_size.height - map_height) / 2 + (root::scene_size.height / 2 - y));
	}

	Texture2D* get_node_texture(GridNodeType type) {
		switch (type) {
		case GRID_NODE_TYPE_FLOOR:				return assets::tex_hex_floor;
		case GRID_NODE_TYPE_WALKABLE_FLOOR:		return assets::tex_hex_walkable_floor;
		case GRID_NODE_TYPE_WALL:				return assets::tex_hex_wall;
		}
		return NULL;
	}
	
	GridNode* get_node(int x, int y) {
		int index = (y * grid_width) + x;
		if (index < 0 || index >= grid_width * grid_height) return NULL;
		return grid_vec[index];
	}

	GridNode* get_neighbour(GridNode* start_node, int offsetx, int offsety) {
		int needs_xoffset = start_node->get_grid_y() % 2 == 0;

		int gx = start_node->get_grid_x() + offsetx;
		int gy = start_node->get_grid_y() + offsety;

		return grid::get_node(gx - ((gy % 2) * needs_xoffset), gy);
	}

	void update() {
		if (input::get_mouse_button_pressed(0)) {
			Vec2 mpos = input::get_mouse_pos();

			for (GridNode* node : grid_vec) {
				Size size = node->get_sprite()->getContentSize();
				size.width *= node->get_sprite()->getScaleX();
				size.height *= node->get_sprite()->getScaleY();

				if (mpos.x >= node->get_world_x() && mpos.x <= node->get_world_x() + size.width &&
					mpos.y >= node->get_world_y() && mpos.y <= node->get_world_y() + size.height) {
					last_clicked_node = node;
					break;
				}
			}
		}
	}
}

/* ================================================================= */

void GridNode::set_type(GridNodeType _type) {
	using namespace grid;

	type = _type;
	update_texture();
}

void GridNode::update_texture() {
	using namespace grid;

	auto tex = get_node_texture(type);
	sprite->setTexture(tex);
	sprite->setTextureRect(Rect(0, 0, sprite->getTexture()->getPixelsWide(), sprite->getTexture()->getPixelsHigh()));
	sprite->setScale(HEX_WIDTH / tex->getPixelsWide(), HEX_HEIGHT / tex->getPixelsHigh());
}