#ifndef _GRID_H_
#define _GRID_H_

#include <vector>

#include <renderer/CCTexture2D.h>
#include <2d/CCSprite.h>

namespace cc = cocos2d;

namespace map {

	enum GridNodeType {

		GRID_NODE_TYPE_NONE,
		GRID_NODE_TYPE_FLOOR,
		GRID_NODE_TYPE_WALKABLE_FLOOR,
		GRID_NODE_TYPE_PLAYER_FLOOR,
		GRID_NODE_TYPE_ENEMY_FLOOR,
		GRID_NODE_TYPE_WALL
	};

	struct NodeTypeProps {

		bool walkable;
		cc::Texture2D* tex;

		void set(bool _walkable, cc::Texture2D* _tex) {
			walkable = _walkable;
			tex = _tex;
		}
	};

	class GridNode {

	public:
		GridNode(int grid_x_, int grid_y_, float world_x_, float world_y_, cc::Sprite* sprite_, GridNodeType type_) :
			grid_x(grid_x_), grid_y(grid_y_),
			world_x(world_x_), world_y(world_y_),
			sprite(sprite_), type(type_)
		{ }

		bool walkable = true;

		void set_type(GridNodeType _type);
		void update_texture();

		int get_grid_x() { return grid_x; }
		int get_grid_y() { return grid_y; }
		float get_world_x() { return world_x; }
		float get_world_y() { return world_y; }
		cc::Sprite* get_sprite() { return sprite; }
		GridNodeType get_type() { return type; }

	private:
		int grid_x;
		int grid_y;
		float world_x;
		float world_y;

		cc::Sprite* sprite;
		GridNodeType type = GRID_NODE_TYPE_NONE;

	};

	const float HEX_SIZE = 80.0f;
	const int HEX_OFFSET = 10;
	const float HEX_WORLD_WIDTH = HEX_SIZE + HEX_OFFSET;
	const float HEX_WORLD_HEIGHT = (HEX_SIZE + HEX_OFFSET) * .8f;

	extern std::vector<GridNode*> grid_vec;
	extern int grid_width;
	extern int grid_height;
	extern float map_width;
	extern float map_height;

	extern cc::Node* node_container;

	extern void init_grid();
	extern void update_grid();
	
	extern std::unique_ptr<NodeTypeProps> get_type_props(GridNodeType type);
	extern GridNode* get_node(int x, int y);
	GridNode* get_neighbour(GridNode* start_node, int offsetx, int offsety);
}

#endif