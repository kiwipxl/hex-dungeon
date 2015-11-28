#include "Grid.h"

#include <2d/CCCamera.h>

#include "Assets.h"
#include "StateManager.h"
#include "entities/Enemy.h"
#include "utility/Logger.h"
#include "utility/Misc.h"

namespace map {

	using namespace cocos2d;

	//private

	//public
	std::vector<GridNode*> grid_vec;
	int grid_width;
	int grid_height;
	float map_width;
	float map_height;

	Node* node_container;
	GridNode* last_clicked_node;

	void init_grid() {
		node_container = Node::create();
		node_container->setAnchorPoint(Vec2(0, 0));
		root::scene->addChild(node_container, 0);

		grid_width = root::scene_size.width / HEX_WORLD_WIDTH;
		grid_height = root::scene_size.height / HEX_WORLD_HEIGHT;
		grid_width *= 1.5f;
		grid_height *= 1.5f;
		map_width = grid_width * HEX_WORLD_WIDTH;
		map_height = grid_height * HEX_WORLD_HEIGHT;

		for (int y = 0; y < grid_height; ++y) {
			for (int x = 0; x < grid_width; ++x) {
				GridNodeType type = GRID_NODE_TYPE_FLOOR;
				if (std::rand() / (float)RAND_MAX >= .8f) type = GRID_NODE_TYPE_WALL;

				auto hex = Sprite::create();
				node_container->addChild(hex, 0);

				hex->setAnchorPoint(Vec2(0, 0));
				hex->setPosition((x + ((y % 2) * .5f)) * HEX_WORLD_WIDTH, y * HEX_WORLD_HEIGHT);

				GridNode* node = new GridNode(
					x, y, 
					hex->getPositionX(), 
					hex->getPositionY(), 
					hex, type);

				node->update_texture();
				
				grid_vec.push_back(node);
			}
		}

		for (int n = 0; n < 10; ++n) {
			entities::Enemy* enemy = entities::create_enemy();
		}
	}
	
	std::unique_ptr<NodeTypeProps> get_type_props(GridNodeType type) {
		std::unique_ptr<NodeTypeProps> props(new NodeTypeProps());

		switch (type) {
		case GRID_NODE_TYPE_FLOOR:				props->set(true, assets::tex_hex_floor); break;
		case GRID_NODE_TYPE_WALKABLE_FLOOR:		props->set(true, assets::tex_hex_walkable_floor); break;
		case GRID_NODE_TYPE_PLAYER_FLOOR:		props->set(false, assets::tex_hex_player_floor); break;
		case GRID_NODE_TYPE_WALL:				props->set(false, assets::tex_hex_wall); break;
		case GRID_NODE_TYPE_ENEMY_FLOOR:		props->set(false, assets::tex_hex_enemy_floor); break;
		}

		return props;
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

		return get_node(gx - ((gy % 2) * needs_xoffset), gy);
	}

	void update_grid() {
		Color3B colour = utility::interp_hue(fmod(root::time_since_startup / 20.0f, 1.0f));
		colour.r = MIN(colour.r + 140, 255);
		colour.g = MIN(colour.g + 140, 255);
		colour.b = MIN(colour.b + 140, 255);

		for (Node* n : node_container->getChildren()) {
			n->setColor(colour);
		}
	}

	/* ================================================================= */

	void GridNode::set_type(map::GridNodeType _type) {
		type = _type;
		update_texture();
	}

	void GridNode::update_texture() {
		std::unique_ptr<NodeTypeProps> props = get_type_props(type);
		walkable = props->walkable;

		auto tex = props->tex;

		sprite->setTexture(tex);
		sprite->setTextureRect(Rect(0, 0, tex->getPixelsWide(), tex->getPixelsHigh()));

		sprite->setScale(HEX_SIZE / tex->getPixelsWide(), HEX_SIZE / tex->getPixelsHigh());
	}
}
