#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <2d/CCSprite.h>

#include "Declares.h"

namespace cc = cocos2d;

namespace entities {

	class Enemy {

	public:
		Enemy();

		cc::Sprite* sprite;
		gui::StatBox* stat_box;

		void update();

	private:
		map::GridNode* current_node;
		cc::Vec2 dest;
		
		void walk_to(map::GridNode* node);
	};

	extern Enemy* create_enemy();
	extern void update_enemies();
};

#endif