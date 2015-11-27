#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <2d/CCSprite.h>

namespace cc = cocos2d;

namespace player {
	
	extern cc::Sprite* sprite;

	extern void init();
	extern void update();
	extern void highlight_neighbours();
};

#endif