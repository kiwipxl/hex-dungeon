#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init()) return false;

    Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setColor(Color3B(33, 33, 33));

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
	label->setPosition(Vec2(origin.x + size.width / 2,
		origin.y + size.height - label->getContentSize().height));

	auto hex_tex = TextureCache::sharedTextureCache()->addImage("hexagon.png");

	auto hex_container = Sprite::create();
	this->addChild(hex_container, 0);
	
	int grid_width = 4;
	int grid_height = 4;
	float hex_width = 64.0f;
	float hex_height = 64.0f;
	int hex_seperation = 10;
	for (int y = 0; y < grid_height; ++y) {
		for (int x = 0; x < grid_width; ++x) {
			auto hex = Sprite::createWithTexture(hex_tex);

			hex->setAnchorPoint(Vec2(.5f, .5f));
			hex->setScale(hex_width / hex_tex->getPixelsWide(), hex_height / hex_tex->getPixelsHigh());
			hex->setPosition(x * (hex_width + hex_seperation), y * (hex_height + hex_seperation));

			hex_container->addChild(hex, 0);
		}
	}
	hex_container->setPosition(size.width / 2, size.height / 2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
