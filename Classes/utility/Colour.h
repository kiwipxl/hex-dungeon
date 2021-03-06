#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <2d/CCNode.h>

namespace cc = cocos2d;

namespace utility {

	class ColourFlash {

	public:
		void start(cc::Node* _target, int _num_flashes, float _flash_seconds, float _max_r, float _max_g, float _max_b);
		void update();

	private:
		cc::Node* target;
		
		int num_flashes;
		float flash_seconds;
		
		bool flashing = false;
		float flash_timer = 0;

		float max_r;
		float max_g;
		float max_b;
	};

	#define IS_BIT(num, lsh) ((num & (1 << (lsh))) != 0)

	/*
	* Interpolates from the top to the bottom range of colours and returns a Color3B.
	* @params (i): value from 0 to 1
	*/
	cc::Color3B interp_hue(float i);
};

#endif