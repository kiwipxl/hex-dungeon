#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <2d/CCSprite.h>

#include "Declares.h"
#include "utility/Colour.h"

namespace cc = cocos2d;

namespace entities {

	class Player {

	public:
		cc::Sprite* sprite;
		gui::StatBox* stat_box;
		map::GridNode* current_node = NULL;

		Player();

		void update();
		void on_node_clicked(map::GridNode* node);
		void refresh_neighbours();

	private:
		cc::Vec2 dest;
		std::vector<map::GridNode*> neighbours;
		utility::ColourFlash colour_flash;

		void take_dmg(float dmg);
		void select_neighbours(map::GridNode* start_node);
		void deselect_neighbours();
		void walk_to(map::GridNode* node);
	};

	extern Player* player;

	extern void init_player();
};

#endif