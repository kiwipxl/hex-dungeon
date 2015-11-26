#include "Grid.h"

namespace grid {

	//public
	std::vector<GridNode*> grid_vec;
	int grid_width;
	int grid_height;
	float map_width;
	float map_height;

	Texture2D* get_node_texture(GridNodeType type) {
		switch (type) {
		case GRID_NODE_TYPE_FLOOR:				return tex_hex_floor;
		case GRID_NODE_TYPE_WALKABLE_FLOOR:		return tex_hex_walkable_floor;
		case GRID_NODE_TYPE_WALL:				return tex_hex_wall;
		}
		return NULL;
	}

	grid::GridNode* get_node(int x, int y) {
		int index = (y * grid_width) + x;
		if (index < 0 || index >= grid_width * grid_height) return NULL;
		return grid_vec[index];
	}

	/* ================================================================= */

	void GridNode::set_type(GridNodeType _type) {
		type = _type;
		update_texture();
	}

	void GridNode::update_texture() {
		auto tex = get_node_texture(type);
		sprite->setTexture(tex);
		sprite->setTextureRect(Rect(0, 0, sprite->getTexture()->getPixelsWide(), sprite->getTexture()->getPixelsHigh()));
		sprite->setScale(HEX_WIDTH / tex->getPixelsWide(), HEX_HEIGHT / tex->getPixelsHigh());
	}
}