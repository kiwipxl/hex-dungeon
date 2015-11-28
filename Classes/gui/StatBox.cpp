#include "StatBox.h"

#include <2d/CCLabel.h>

#include "Assets.h"
#include "StateManager.h"
#include "utility/Logger.h"

namespace gui {

	using namespace cocos2d;

	StatBox::StatBox(float _max_hp, float _max_dmg) {
		max_hp = _max_hp;
		hp = max_hp;

		max_dmg = _max_dmg;
		dmg = max_dmg;

		box = Sprite::createWithTexture(assets::tex_char_stats);
		box->setAnchorPoint(Vec2(0, 0));
		box->setZOrder(1000);
		root::scene->addChild(box);

		hp_text = Label::create("0", "fonts/Arial.ttf", 15);
		hp_text->setAnchorPoint(Vec2(0, 0));
		hp_text->setPosition(17, 1);
		box->addChild(hp_text);

		dmg_text = Label::create("0", "fonts/Arial.ttf", 15);
		dmg_text->setAnchorPoint(Vec2(0, 0));
		dmg_text->setPosition(54, 1);
		box->addChild(dmg_text);

		set_hp(max_hp);
		set_dmg(max_dmg);
	}

	void StatBox::set_hp(float _hp) {
		hp = _hp;
		hp_text->setString(sstream_cstr(hp));

		if (hp != _hp) hp_text->setTextColor(Color4B(255, 180, 180, 255));
	}

	void StatBox::set_dmg(float _dmg) {
		dmg = _dmg;
		dmg_text->setString(sstream_cstr(dmg));
	}
};