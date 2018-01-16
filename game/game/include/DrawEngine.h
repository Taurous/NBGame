#pragma once

#include "Util\Logger.h"
#include "Util\Timer.h" // For cursor blinking

#include "Window.h"
#include "ResourceManager.h"
#include "ResourceTypes.h"

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <vector>
#include <string>

namespace axe
{
	const int TEXT_JITTER = 8;

	class DrawEngine
	{
	public:
		DrawEngine();
		~DrawEngine();

		int init(Window *window);
		void handleEvents(const ALLEGRO_EVENT &ev);
		void cleanUp();

		int getWindowWidth() { return m_window->getScreenWidth(); }
		int getWindowHeight() { return m_window->getScreenHeight(); }

		bool getWindowFullscreen() { return m_window->getFullscreen(); }

		void drawText(ResourceHandle<Font> font, ALLEGRO_COLOR cl, float x, float y, int flags, std::string text);
		void drawTextF(ResourceHandle<Font> font, ALLEGRO_COLOR cl, float x, float y, int flags, std::string format, ...);
		void drawTextWithCursor(ResourceHandle<Font> font, ALLEGRO_COLOR cl, float x, float y, int flags, m_secs speed, unsigned int string_length, std::string text);
		void drawTextNewLine(ResourceHandle<Font> font, ALLEGRO_COLOR cl, float x, float y, int spacing, int flags, std::string text);
		void drawTextNewLineWithCursor(ResourceHandle<Font> font, ALLEGRO_COLOR cl, float x, float y, int spacing, int flags, m_secs speed, unsigned int string_length, std::string text);

		void drawBitmap(ResourceHandle<Bitmap> bmp, int x, int y, int flags);
		void drawScaledBitmap(ResourceHandle<Bitmap> bmp, int x, int y, float x_scale, float y_scale, int flags);
		void drawScaledBitmap(ResourceHandle<Bitmap> bmp, int x, int y, int width, int height, int flags);

		int formatStringByWidth(const ResourceHandle<Font> &font, int max_string_width, std::string &str); // returns number of rows of text after formatting

		void flipAndClear(ALLEGRO_COLOR cl);

		ResourceManager<Bitmap> bitmaps;
		ResourceManager<Font> fonts;

	private:
		Window *m_window;
		Timer t_cursorFlash;

	};
};