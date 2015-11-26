#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

enum GridNodeType {

	GRID_NODE_TYPE_NONE,
	GRID_NODE_TYPE_FLOOR,
	GRID_NODE_TYPE_WALKABLE_FLOOR,
	GRID_NODE_TYPE_WALL
};


float HEX_WIDTH = 64.0f;
float HEX_HEIGHT = 64.0f;
int HEX_OFFSET = 10;
float HEX_WORLD_WIDTH = HEX_WIDTH + HEX_OFFSET;
float HEX_WORLD_HEIGHT = (HEX_HEIGHT + HEX_OFFSET) * .8f;

Texture2D* tex_hex_floor;
Texture2D* tex_hex_wall;
Texture2D* tex_hex_walkable_floor;
Texture2D* tex_char_warrior;

Texture2D* get_node_texture(GridNodeType type) {
	switch (type) {
	case GRID_NODE_TYPE_FLOOR:				return tex_hex_floor;
	case GRID_NODE_TYPE_WALKABLE_FLOOR:		return tex_hex_walkable_floor;
	case GRID_NODE_TYPE_WALL:				return tex_hex_wall;
	}
	return NULL;
}

struct GridNode {

	int grid_x;
	int grid_y;
	float world_x;
	float world_y;

	Sprite* sprite;
	GridNodeType type = GRID_NODE_TYPE_NONE;

	void update_texture() {
		auto tex = get_node_texture(type);
		sprite->setTexture(tex);
		sprite->setScale(HEX_WIDTH / tex->getPixelsWide(), HEX_HEIGHT / tex->getPixelsHigh());
	}
};

std::vector<GridNode*> grid;
int grid_width;
int grid_height;
float map_width;
float map_height;

GridNode* get_node(int x, int y) {
	int index = (y * grid_width) + x;
	if (index < 0 || index >= grid_width * grid_height) return NULL;
	return grid[index];
}

void move_to(Sprite* sprite, GridNode* node) {
	sprite->setPosition(node->world_x, node->world_y + (HEX_HEIGHT * .35f));
}

bool HelloWorld::init()
{
	if (!LayerColor::initWithColor(Color4B(12, 12, 12, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	
	tex_hex_floor = TextureCache::getInstance()->addImage("hex_floor.png");
	tex_hex_walkable_floor = TextureCache::getInstance()->addImage("hex_walkable_floor.png");
	tex_hex_wall = TextureCache::getInstance()->addImage("hex_wall.png");
	tex_char_warrior = TextureCache::getInstance()->addImage("char_warrior.png");

	auto hex_container = Sprite::create();
	this->addChild(hex_container, 0);

	grid_width = size.width / HEX_WORLD_WIDTH;
	grid_height = size.height / HEX_WORLD_HEIGHT;
	--grid_width;
	--grid_height;
	map_width = grid_width * HEX_WORLD_WIDTH;
	map_height = grid_height * HEX_WORLD_HEIGHT;

	hex_container->setPosition((size.width - map_width) / 2, (size.height - map_height) / 2);

	for (int y = 0; y < grid_height; ++y) {
		for (int x = 0; x < grid_width; ++x) {
			GridNodeType type = GRID_NODE_TYPE_FLOOR;
			if (x % 4 <= 1) type = GRID_NODE_TYPE_WALL;

			auto hex = Sprite::create();
			hex_container->addChild(hex, 0);

			hex->setAnchorPoint(Vec2(0, 0));
			hex->setPosition((x + ((y % 2) * .5f)) * HEX_WORLD_WIDTH, y * HEX_WORLD_HEIGHT);

			GridNode* node = new GridNode();
			node->grid_x = x;
			node->grid_y = y;
			node->world_x = hex->getPositionX() + hex_container->getPositionX();
			node->world_y = hex->getPositionY() + hex_container->getPositionY();
			node->type = type;
			node->sprite = hex;

			node->update_texture();

			grid.push_back(node);
		}
	}

	auto char_warrior = Sprite::createWithTexture(tex_char_warrior);
	char_warrior->setAnchorPoint(Vec2(0, 0));
	move_to(char_warrior, get_node(grid_width / 2, grid_height / 2));
	this->addChild(char_warrior);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt) {

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
