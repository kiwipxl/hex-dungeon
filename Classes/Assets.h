#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <renderer/CCTexture2D.h>
#include <renderer/CCTextureCache.h>

namespace assets {

	namespace cc = cocos2d;

	extern cc::Texture2D* tex_hex_floor;
	extern cc::Texture2D* tex_hex_wall;
	extern cc::Texture2D* tex_hex_walkable_floor;
	extern cc::Texture2D* tex_hex_player_floor;
	extern cc::Texture2D* tex_hex_enemy_floor;

	extern cc::Texture2D* tex_char_warrior;
	extern cc::Texture2D* tex_char_skeleton;

	extern void init();
};

#endif