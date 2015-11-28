#include "StateManager.h"

#include <base/CCDirector.h>

#include "Assets.h"
#include "entities/Enemy.h"
#include "entities/Player.h"
#include "map/Grid.h"
#include "map/TurnControl.h"

#include "input/KeyboardInput.h"
#include "input/MouseInput.h"

#include "utility/Logger.h"

namespace root {

	using namespace cocos2d;

	//private
	void create_state(State new_state) {
		if (state == new_state) return;

		state = new_state;

		switch (state) {
		case STATE_GAME:
			assets::init();
			map::init_grid();
			map::init_turns();
			entities::init_player();

			break;
		}
	}

	void remove_state(State new_state) {
		if (state == new_state) return;

		state = new_state;

		switch (state) {
		case STATE_GAME:
			break;
		}
	}

	//public
	Scene* scene;
	State state = STATE_EMPTY;

	float time_since_startup = 0;
	float delta_time = 0;
	Size scene_size;

	void init_root(SceneInit* scene_ref) {
		scene = (Scene*)scene_ref;
		srand(time(NULL));

		scene_size = Director::getInstance()->getVisibleSize();

		input::init_keyboard();
		input::init_mouse();
		utility::init_logger();

		//initial state when game is initialised
		create_state(STATE_GAME);
	}

	void switch_state(State new_state) {
		if (state == new_state) return;

		remove_state(state);
		state = new_state;
		create_state(state);
	}

	void update_state(float dt) {
		time_since_startup += dt;
		delta_time = dt;

		switch (state) {
		case STATE_GAME:
			map::update_grid();
			map::update_turns();
			entities::player->update();
			entities::update_enemies();

			break;
		}

		input::update_keyboard();
		input::update_mouse();
	}
};