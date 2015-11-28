#include "Colour.h"

#include "StateManager.h"
#include "utility/Logger.h"

using namespace cocos2d;

namespace utility {
	
	void ColourFlash::start(cc::Node* _target, int _num_flashes, float _flash_seconds, float _max_r, float _max_g, float _max_b) {
		target = _target;
		num_flashes = _num_flashes;
		flash_seconds = _flash_seconds;
		max_r = _max_r;
		max_g = _max_g;
		max_b = _max_b;

		flashing = true;
		flash_timer = 0;
	}

	void ColourFlash::update() {
		if (!target) flashing = false;

		if (flashing) {
			flash_timer += root::delta_time / flash_seconds;

			//lerp between 0 to 1 and then 1 to 0 x times, specified by num_flashes
			float x = fmod(flash_timer, 1.0f / num_flashes);
			float c = 1.0f - ((x < (.5f / num_flashes)) ? x : ((1.0f / num_flashes) - x)) * 2.0f;
			
			//lerp between max_r to 1, max_g to 1 and max_b to 1
			target->setColor(Color3B(
				(max_r + ((1.0f - max_r) * c)) * 255.0f,
				(max_g + ((1.0f - max_g) * c)) * 255.0f,
				(max_b + ((1.0f - max_b) * c)) * 255.0f));

			if (flash_timer >= 1) flashing = false;
		}
	}

	cc::Color3B interp_hue(float i) {
		int i7 = (int)(i * 6);
		float f7 = fmod(i * 6, 1.0f);

		return cc::Color3B(
			(IS_BIT(0x63, i7) + ((IS_BIT(0x63, i7 + 1) - IS_BIT(0x63, i7)) * f7)) * 255,
			(IS_BIT(0x38, i7) + ((IS_BIT(0x38, i7 + 1) - IS_BIT(0x38, i7)) * f7)) * 255,
			(IS_BIT(0x0E, i7) + ((IS_BIT(0x0E, i7 + 1) - IS_BIT(0x0E, i7)) * f7)) * 255);
	}
};