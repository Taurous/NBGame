#pragma once

#include <allegro5\allegro_native_dialog.h>

namespace axe
{
	enum
	{
		LOGGER_ERROR,
		LOGGER_WARNING,
		LOGGER_MESSAGE

	};

	void setOutputFile(const char *file);
	void log(int type, const char *fmt, ...);
	void crash(const char *fmt, ...);
};