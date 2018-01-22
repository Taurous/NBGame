#pragma once

#include "Util\Logger.h"
#include <allegro5\allegro.h>
#include <string>

namespace axe
{
	class Window
	{
	public:
		Window();
		~Window();

		bool create(int width, int height, std::string title, std::string icon_path = "", int flags = ALLEGRO_WINDOWED);

		void setWindowIcon(std::string path);
		void setWindowTitle(std::string title);

		bool getFullscreen() const { return (m_flags & ALLEGRO_FULLSCREEN || m_flags & ALLEGRO_FULLSCREEN_WINDOW); }
		int getScreenWidth() const { return m_width; }
		int getScreenHeight() const { return m_height; }

		void registerForEvents(ALLEGRO_EVENT_QUEUE *eq);
		ALLEGRO_DISPLAY *getAllegroDisplay() { return m_display; }

		void centerWindow(); // Untested

		void printDisplayModes();

	private:
		bool createWindow();

		ALLEGRO_MONITOR_INFO *m_monitor_info;
		ALLEGRO_DISPLAY_MODE *m_display_mode;

		ALLEGRO_DISPLAY *m_display;
		ALLEGRO_BITMAP *m_icon;
		ALLEGRO_EVENT_QUEUE *m_event_queue;

		std::string m_title;
		std::string m_icon_path;

		int m_flags;
		int m_width;
		int m_height;

		int m_current_display_mode;
	};
}