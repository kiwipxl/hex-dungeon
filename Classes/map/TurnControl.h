#ifndef _TURN_CONTROL_H_
#define _TURN_CONTROL_H_

#include <2d/CCCamera.h>

#include "Declares.h"

namespace cc = cocos2d;

namespace map {
	
	extern cc::Camera* camera;

	extern void init_turns();
	extern void update_turns();
};

#endif