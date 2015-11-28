#include "StatBox.h"

#include <2d/CCLabel.h>

#include "Assets.h"
#include "StateManager.h"
#include "utility/Logger.h"

namespace gui {

	using namespace cocos2d;

	StatBox::StatBox() {
		box = Sprite::createWithTexture(assets::tex_char_stats);
		box->setAnchorPoint(Vec2(0, 0));
		box->setZOrder(1000);
		root::scene->addChild(box);

		hp_text = Label::create("99", "fonts/Arial.ttf", 15);
		hp_text->setAnchorPoint(Vec2(0, 0));
		hp_text->setPosition(17, 1);
		box->addChild(hp_text);

		dmg_text = Label::create("99", "fonts/Arial.ttf", 15);
		dmg_text->setAnchorPoint(Vec2(0, 0));
		dmg_text->setPosition(54, 1);
		box->addChild(dmg_text);
	}
};