#ifndef _MISC_H_
#define _MISC_H_

#include <2d/CCNode.h>

namespace cc = cocos2d;

namespace utility {

	/*
	* Interpolates from the top to the bottom range of colours and returns a Color3B.
	* @params (i): value from 0 to 1
	*/

	#define IS_BIT(num, lsh) ((num & (1 << (lsh))) != 0)

	cc::Color3B interp_hue(float i) {
		int i7 = (int)(i * 6);
		float f7 = fmod(i * 6, 1.0f);

		return cc::Color3B(
			(IS_BIT(0x63, i7) + ((IS_BIT(0x63, i7 + 1) - IS_BIT(0x63, i7)) * f7)) * 255,
			(IS_BIT(0x38, i7) + ((IS_BIT(0x38, i7 + 1) - IS_BIT(0x38, i7)) * f7)) * 255,
			(IS_BIT(0x0E, i7) + ((IS_BIT(0x0E, i7 + 1) - IS_BIT(0x0E, i7)) * f7)) * 255);
	}
};

#endif