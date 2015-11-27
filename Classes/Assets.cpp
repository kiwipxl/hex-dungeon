#include "Assets.h"

using namespace cocos2d;

namespace assets {

	Texture2D* tex_hex_floor;
	Texture2D* tex_hex_wall;
	Texture2D* tex_hex_walkable_floor;
	Texture2D* tex_hex_player_floor;
	Texture2D* tex_hex_enemy_floor;

	Texture2D* tex_char_warrior;
	Texture2D* tex_char_skeleton;

	void init() {
		tex_hex_floor = TextureCache::getInstance()->addImage("hex_floor.png");
		tex_hex_walkable_floor = TextureCache::getInstance()->addImage("hex_walkable_floor.png");
		tex_hex_wall = TextureCache::getInstance()->addImage("hex_wall.png");
		tex_hex_player_floor = TextureCache::getInstance()->addImage("hex_player_floor.png");
		tex_hex_enemy_floor = TextureCache::getInstance()->addImage("hex_enemy_floor.png");

		tex_char_warrior = TextureCache::getInstance()->addImage("char_warrior.png");
		tex_char_skeleton = TextureCache::getInstance()->addImage("char_skeleton.png");
	}
};