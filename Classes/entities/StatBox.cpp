#include "StatBox.h"

#include <2d/CCLabel.h>

#include "Assets.h"
#include "StateManager.h"
#include "utility/Logger.h"

namespace entities {

	using namespace cocos2d;

	StatBox::StatBox() {
		box = Sprite::createWithTexture(assets::tex_char_stats);
		box->setAnchorPoint(Vec2(0, 0));
		box->setZOrder(1000);
		root::scene->addChild(box);

		hp_text = Label::create("4", "fonts/Marker Felt.ttf", 12);
		hp_text->setAnchorPoint(Vec2(0, 0));
		hp_text->setPosition(20, 2);
		box->addChild(hp_text);

		dmg_text = Label::create("8", "fonts/Marker Felt.ttf", 12);
		dmg_text->setAnchorPoint(Vec2(0, 0));
		dmg_text->setPosition(57, 2);
		box->addChild(dmg_text);
	}
};