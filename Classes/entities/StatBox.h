#ifndef _STAT_BOX_H_
#define _STAT_BOX_H_

#include <2d/CCSprite.h>
#include <2d/CCLabel.h>

namespace cc = cocos2d;

namespace entities {

	class StatBox {

	public:
		cc::Sprite* box;
		cc::Label* dmg_text;
		cc::Label* hp_text;

		StatBox();
	};
};

#endif