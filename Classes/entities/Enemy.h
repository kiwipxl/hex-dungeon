#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <2d/CCSprite.h>

#include "Declares.h"
#include "utility/Colour.h"

namespace cc = cocos2d;

namespace entities {

	class Enemy {

	public:
		Enemy();

		cc::Sprite* sprite;
		gui::StatBox* stat_box;
		map::GridNode* current_node = NULL;

		void update();
		void remove();
		void deal_dmg(float dmg);

		bool is_removal_scheduled() { return removal_scheduled; }

	private:
		cc::Vec2 dest;
		utility::ColourFlash colour_flash;
		bool removal_scheduled = false;

		void walk_to(map::GridNode* node);
	};
	
	extern std::vector<Enemy*> enemies;

	extern Enemy* create_enemy();
	extern void update_enemies();
};

#endif