#include "utility/Logger.h"

#include <assert.h>
#include <fstream>

#include <base/CCConsole.h>

namespace utility {

	//private
	std::ofstream lfile;

	//public
	StrStream glb_stream;

	void init_logger() {
		lfile.open("log.txt");
	}

	//-- begin Logger class --

	Logger::~Logger() {
		if (!(action & ACTION_NO_NEW_LINE)) stream << '\n';

		if (action & ACTION_SAVE_TO_FILE) {
			lfile.write(stream.str().c_str(), stream.str().length());
			lfile.flush();
		}
		if (action & ACTION_PRINT) {
			if (action & ACTION_INFO) {
				cocos2d::log("%s", stream.str().c_str());
			}
			else if (action & ACTION_WARNING) {
				cocos2d::log("%s", stream.str().c_str());
			}
			else if (action & ACTION_ERROR) {
				cocos2d::log("%s", stream.str().c_str());
			}
			else if (action & ACTION_MID) {
				cocos2d::log("%s", stream.str().c_str());
			}
		}
	}
};