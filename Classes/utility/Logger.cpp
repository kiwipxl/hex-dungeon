#include "utility/Logger.h"

#include <assert.h>

#include <base/CCConsole.h>

namespace utility {

	//private
	std::FILE* lfile;

	//public
	StrStream glb_stream;

	void init_logger() {
		lfile = fopen("log.txt", "w");
		assert(lfile != NULL && sstream_cstr("log.txt could not be written"));
	}

	//-- begin Logger class --

	Logger::~Logger() {
		if (!(action & ACTION_NO_NEW_LINE)) stream << '\n';

		if (action & ACTION_SAVE_TO_FILE) {
			fwrite(stream.str().c_str(), stream.str().length(), 1, lfile);
			fflush(lfile);
		}
		if (action & ACTION_PRINT) {
			if (action & ACTION_INFO) {
				cocos2d::log(stream.str().c_str());
			}
			else if (action & ACTION_WARNING) {
				cocos2d::log(stream.str().c_str());
			}
			else if (action & ACTION_ERROR) {
				cocos2d::log(stream.str().c_str());
			}
			else if (action & ACTION_MID) {
				cocos2d::log(stream.str().c_str());
			}
		}
	}
};