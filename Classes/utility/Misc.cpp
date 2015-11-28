#include "Misc.h"

#include "map/TurnControl.h"
#include "StateManager.h"

using namespace cocos2d;

namespace utility {

	//private
	float shake_duration;
	float shake_intensity;
	float shake_timer = 0;
	bool shaking = false;

	//public

	void shake_screen(float duration, float intensity) {
		shake_duration = duration;
		shake_intensity = intensity;
		shake_timer = 0;
		shaking = true;
	}

	void update_misc() {
		float camx = map::camera->getPositionX();
		float camy = map::camera->getPositionY();

		if (shaking) {
			shake_timer += root::delta_time;

			camx += ((rand() / (float)RAND_MAX) - .5f) * shake_intensity * 2;
			camy += ((rand() / (float)RAND_MAX) - .5f) * shake_intensity * 2;
			map::camera->setPosition(camx, camy);

			if (shake_timer >= shake_duration) shaking = false;
		}
	}
};