#include "input/MouseInput.h"

#include <base/CCEventDispatcher.h>
#include <base/CCEventMouse.h>
#include <base/CCEventListenerMouse.h>
#include <base/CCEventTouch.h>
#include <base/CCEventListenerTouch.h>
#include <base/CCEventListener.h>
#include "cocos2d.h"

#include "utility/Logger.h"

#include "StateManager.h"

using namespace cocos2d;

namespace input {

	//private
	EventListenerMouse* mouse_listener;
	EventListenerTouchOneByOne* touch_listener;

	struct MouseButton {

		bool down = false;
		bool pressed = false;
	};

	struct MouseData {

		Vec2 pos;
		Vec2 scroll;

		MouseButton button_left;
		MouseButton button_right;
		MouseButton button_undefined;
	} mouse;

	MouseButton& get_mouse_button(int button) {
		switch (button) {
		case MOUSE_BUTTON_LEFT:
			return mouse.button_left;
			break;
		case MOUSE_BUTTON_RIGHT:
			return mouse.button_right;
			break;
		default:
			return mouse.button_undefined;
		}
	}

	void init_mouse() {
		mouse_listener = EventListenerMouse::create();
		touch_listener = EventListenerTouchOneByOne::create();

		mouse_listener->onMouseDown = [](EventMouse* em) {
			get_mouse_button(em->getMouseButton()).down = true;
			get_mouse_button(em->getMouseButton()).pressed = true;
		};

		mouse_listener->onMouseUp = [](EventMouse* em) {
			get_mouse_button(em->getMouseButton()).down = false;
			get_mouse_button(em->getMouseButton()).pressed = false;
		};

		mouse_listener->onMouseMove = [](EventMouse* em) {
			mouse.pos.x = em->getCursorX();
			mouse.pos.y = em->getCursorY();
		};

		mouse_listener->onMouseScroll = [](EventMouse* em) {
			mouse.scroll.x = em->getScrollX();
			mouse.scroll.y = em->getScrollY();
		};

		touch_listener->onTouchBegan = [](Touch* touch, Event* e) {
			get_mouse_button(0).down = true;
			get_mouse_button(0).pressed = true;

			mouse.pos.x = touch->getLocation().x;
			mouse.pos.y = touch->getLocation().y;

			return true;
		};

		touch_listener->onTouchEnded = [](Touch* touch, Event* e) {
			get_mouse_button(0).down = false;
			get_mouse_button(0).pressed = false;

			mouse.pos.x = touch->getLocation().x;
			mouse.pos.y = touch->getLocation().y;
		};

		touch_listener->onTouchMoved = [](Touch* touch, Event* e) {
			mouse.pos.x = touch->getLocation().x;
			mouse.pos.y = touch->getLocation().y;
		};

		root::scene->getEventDispatcher()->addEventListenerWithFixedPriority(mouse_listener, 1);
		root::scene->getEventDispatcher()->addEventListenerWithFixedPriority(touch_listener, 1);
	}

	bool get_mouse_button_pressed(int mouse_button) {
		return get_mouse_button(mouse_button).pressed;
	}

	bool get_mouse_button_down(int mouse_button) {
		return get_mouse_button(mouse_button).down;
	}

	Vec2 get_mouse_pos() {
		return mouse.pos;
	}

	Vec2 get_mouse_scroll() {
		return mouse.scroll;
	}

	void update_mouse() {
		mouse.button_left.pressed = false;
		mouse.button_right.pressed = false;
		mouse.scroll = { 0, 0 };
	}
};