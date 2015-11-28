#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <2d/CCSprite.h>

class GridNode;

namespace cc = cocos2d;

namespace entities {

	class StatBox;

	class Enemy {

	public:
		Enemy();

		cc::Sprite* sprite;
		StatBox* stat_box;

		void update();

	private:
		GridNode* current_node;
		cc::Vec2 dest;
		
		void walk_to(GridNode* node);
	};

	extern Enemy* create_enemy();
	extern void update_enemies();
};

#endif