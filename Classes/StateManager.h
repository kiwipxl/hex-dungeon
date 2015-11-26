#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include "SceneInit.h"

namespace root {

	namespace cc = cocos2d;

	enum State {

		STATE_EMPTY,
		STATE_GAME
	};

	extern cc::Scene* scene;
	extern State state;

	extern float time_since_startup;
	extern float delta_time;
	extern cc::Size scene_size;

	extern void init_root(SceneInit* scene_ref);
	extern void update_state(float dt);
	extern void switch_state(State new_state);
};

#endif