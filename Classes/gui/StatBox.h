#ifndef _STAT_BOX_H_
#define _STAT_BOX_H_

#include <2d/CCSprite.h>
#include <2d/CCLabel.h>

namespace cc = cocos2d;

namespace gui {

	class StatBox {

	public:
		float hp;
		float max_hp;
		float dmg;
		float max_dmg;

		cc::Sprite* box;
		cc::Label* hp_text;
		cc::Label* dmg_text;

		StatBox(float _max_hp, float _max_dmg);

		void set_hp(float _hp);
		void set_dmg(float _dmg);
	};
};

#endif