#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <2d/CCSprite.h>

namespace cc = cocos2d;

namespace entities {
	
	class StatBox;
	
	extern cc::Sprite* sprite;
	extern StatBox* stat_box;

	extern void init_player();
	extern void update_player();
};

#endif