#include "Grid.h"

#include "Assets.h"
#include "StateManager.h"

namespace grid {

	using namespace cocos2d;

	//public
	std::vector<GridNode*> grid_vec;
	int grid_width;
	int grid_height;
	float map_width;
	float map_height;

	void init() {
		auto hex_container = Sprite::create();
		root::scene->addChild(hex_container, 0);

		grid_width = root::scene_size.width / HEX_WORLD_WIDTH;
		grid_height = root::scene_size.height / HEX_WORLD_HEIGHT;
		--grid_width;
		--grid_height;
		grid_height = 2;
		map_width = grid_width * HEX_WORLD_WIDTH;
		map_height = grid_height * HEX_WORLD_HEIGHT;

		hex_container->setPosition((root::scene_size.width - map_width) / 2, (root::scene_size.height - map_height) / 2);

		for (int y = 0; y < grid_height; ++y) {
			for (int x = 0; x < grid_width; ++x) {
				GridNodeType type = GRID_NODE_TYPE_FLOOR;
				if (x % 4 <= 1) type = GRID_NODE_TYPE_WALL;

				auto hex = Sprite::create();
				hex_container->addChild(hex, 0);

				hex->setAnchorPoint(Vec2(0, 0));
				hex->setPosition((x + ((y % 2) * .5f)) * HEX_WORLD_WIDTH, y * HEX_WORLD_HEIGHT);

				GridNode* node = new GridNode(
					x, y, 
					hex->getPositionX() + hex_container->getPositionX(), 
					hex->getPositionY() + hex_container->getPositionY(), 
					hex, type);

				node->update_texture();
				
				grid_vec.push_back(node);
			}
		}
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

	void update() {
		for (GridNode* node : grid_vec) {

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