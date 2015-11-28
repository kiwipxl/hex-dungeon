#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <2d/CCSprite.h>

#include "Declares.h"

namespace cc = cocos2d;

namespace entities {

	extern cc::Sprite* sprite;
	extern gui::StatBox* stat_box;

	extern void init_player();
	extern void update_player();
};

#endif