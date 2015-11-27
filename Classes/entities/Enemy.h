#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <2d/CCSprite.h>

class GridNode;

namespace cc = cocos2d;

namespace enemy {

	class Enemy {

	public:
		Enemy();

		cc::Sprite* sprite;

		void init();
		void update();

	private:
		GridNode* current_node;
		cc::Vec2 dest;
		
		void walk_to(GridNode* node);
	};

	extern Enemy* create_enemy();
	extern void update();
};

#endif