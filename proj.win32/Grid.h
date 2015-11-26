#ifndef _GRID_H_
#define _GRID_H_

#include <vector>

#include <renderer/CCTexture2D.h>
#include <2d/CCSprite.h>

namespace grid {

	using namespace cocos2d;

	enum GridNodeType {

		GRID_NODE_TYPE_NONE,
		GRID_NODE_TYPE_FLOOR,
		GRID_NODE_TYPE_WALKABLE_FLOOR,
		GRID_NODE_TYPE_WALL
	};

	class GridNode {

		int grid_x;
		int grid_y;
		float world_x;
		float world_y;

		Sprite* sprite;
		GridNodeType type = GRID_NODE_TYPE_NONE;

		void set_type(GridNodeType _type);
		void update_texture();
	};

	const float HEX_WIDTH = 64.0f;
	const float HEX_HEIGHT = 64.0f;
	const int HEX_OFFSET = 10;
	const float HEX_WORLD_WIDTH = HEX_WIDTH + HEX_OFFSET;
	const float HEX_WORLD_HEIGHT = (HEX_HEIGHT + HEX_OFFSET) * .8f;

	extern std::vector<GridNode*> grid_vec;
	extern int grid_width;
	extern int grid_height;
	extern float map_width;
	extern float map_height;

	extern Texture2D* get_node_texture(GridNodeType type);
	extern GridNode* get_node(int x, int y);
}

#endif