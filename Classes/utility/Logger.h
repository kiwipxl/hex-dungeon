#ifndef _LOGGER_H_
#define _LOGGER_H_

/*
handles all debug/release logging to console and to file
*/

#include <stdio.h>

#include <iostream>
#include <sstream>
#include <functional>

namespace utility {

	/* ================================================================= */
	// Str Stream

	#define sstream_str(x)      (utility::glb_stream.clear() << x << '\0').stream.str()
	#define sstream_cstr(x)     (utility::glb_stream.clear() << x << '\0').stream.str().c_str()

	class StrStream {

	public:
		std::stringstream stream;

		StrStream& clear() {
			stream.str("");
			return *this;
		}

		template<class T> StrStream& operator<<(const T& v) {
			stream << v;
			return *this;
		}
	};

	extern StrStream glb_stream;

	/* ================================================================= */
	// Logging

	#define log_file            utility::Logger(utility::ACTION_INFO | utility::ACTION_SAVE_TO_FILE)
	#define log_print           utility::Logger(utility::ACTION_INFO | utility::ACTION_PRINT)
	#define log_print_file      utility::Logger(utility::ACTION_INFO | utility::ACTION_SAVE_TO_FILE | utility::ACTION_PRINT)

	#define log_info            utility::Logger(utility::ACTION_INFO | utility::ACTION_SAVE_TO_FILE | utility::ACTION_PRINT)
	#define log_warning         utility::Logger(utility::ACTION_WARNING | utility::ACTION_SAVE_TO_FILE | utility::ACTION_PRINT)
	#define log_error           utility::Logger(utility::ACTION_WARNING | utility::ACTION_SAVE_TO_FILE | utility::ACTION_PRINT)

	#define log_mid             utility::Logger(utility::ACTION_MID | utility::ACTION_SAVE_TO_FILE)

	extern void init_logger();

	enum LogAction {

		ACTION_INFO = 1 << 1,
		ACTION_WARNING = 1 << 2,
		ACTION_ERROR = 1 << 3,
		ACTION_MID = 1 << 4,

		ACTION_NO_NEW_LINE = 1 << 5,

		ACTION_SAVE_TO_FILE = 1 << 6,
		ACTION_PRINT = 1 << 7,
	};

	class Logger {

	public:
		Logger(LogAction laction) {
			action = laction;
		}

		Logger(int laction) {
			action = (LogAction)laction;
		}

		std::stringstream stream;
		LogAction action;

		template<class T> Logger& operator<<(const T& v) {
			stream << v;
			return *this;
		}

		Logger& operator<<(const LogAction& v) {
			action = (LogAction)(action | v);
			return *this;
		}

		~Logger();
	};
}

#endif