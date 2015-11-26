#include "Assets.h"

namespace assets {

	using namespace cocos2d;

	Texture2D* tex_hex_floor;
	Texture2D* tex_hex_wall;
	Texture2D* tex_hex_walkable_floor;
	Texture2D* tex_char_warrior;

	void init() {
		tex_hex_floor = TextureCache::getInstance()->addImage("hex_floor.png");
		tex_hex_walkable_floor = TextureCache::getInstance()->addImage("hex_walkable_floor.png");
		tex_hex_wall = TextureCache::getInstance()->addImage("hex_wall.png");
		tex_char_warrior = TextureCache::getInstance()->addImage("char_warrior.png");
	}
};