#include "Window.h"

namespace axe
{
	Window::Window()
		:	m_width(0)
		,	m_height(0)
		,	m_title("")
		,	m_icon_path("")
		,	m_flags(0)
		,	m_display(nullptr)
		,	m_event_queue(nullptr)
		,	m_icon(nullptr)
		,	m_monitor_info(nullptr)
		,	m_display_mode(nullptr)
		,	m_current_display_mode(0)
	{
		
	}

	Window::~Window()
	{
		delete[] m_monitor_info;
		delete[] m_display_mode;

		if (m_icon) al_destroy_bitmap(m_icon);
		if (m_display) al_destroy_display(m_display);

		m_icon = nullptr;
		m_display = nullptr;
	}

	bool Window::create(int width, int height, std::string title, std::string icon_path, int flags)
	{
		m_width = width;
		m_height = height;
		m_title = title;
		m_icon_path = icon_path;
		m_flags = flags;

		int num_display_adapters = al_get_num_video_adapters();
		m_monitor_info = new ALLEGRO_MONITOR_INFO[num_display_adapters];
		printf("\nNumber of display adapters detected: %i\n", num_display_adapters);
		for (int i = 0; i < num_display_adapters; ++i)
		{
			al_get_monitor_info(i, &m_monitor_info[i]);
			int x = m_monitor_info[i].x1;
			int y = m_monitor_info[i].y1;
			int w = m_monitor_info[i].x2 - m_monitor_info[i].x1;
			int h = m_monitor_info[i].y2 - m_monitor_info[i].y1;
			printf("Monitor %i Resolution: %ix%i", i, w-x, h-y);
		}
		printf("\n");

		int num_display_modes = al_get_num_display_modes();
		m_display_mode = new ALLEGRO_DISPLAY_MODE[num_display_modes];
		for (int i = 0; i < num_display_modes; ++i)
		{
			al_get_display_mode(i, &m_display_mode[i]);
		}

		//printDisplayModes();

		return createWindow();
	}

	void Window::printDisplayModes()
	{
		int num_display_modes = al_get_num_display_modes();
		for (int i = 0; i < num_display_modes; i += 2)
		{
			// Redo display mode printing
			if (i + 1 < num_display_modes)
			{
				printf("Display Mode %02i:\t\t\t\t\tDisplay Mode %02i:\n", i, i + 1);
				printf("\tFormat: %i\t\t\t\t\tFormat: %i\n", m_display_mode[i].format, m_display_mode[i + 1].format);
				printf("\tRefresh Rate: %i\t\t\t\tRefresh Rate: %i\n", m_display_mode[i].refresh_rate, m_display_mode[i + 1].refresh_rate);
				printf("\tResolution: %ix%i\t\t\t\tResolution: %ix%i\n\n", m_display_mode[i].width, m_display_mode[i].height, m_display_mode[i + 1].width, m_display_mode[i + 1].height);
			}
			else
			{
				printf("Display Mode %i:\n\tformat: %i\n\trefresh rate: %i\n\tresolution: %ix%i\n", i, m_display_mode[i].format, m_display_mode[i].refresh_rate, m_display_mode[i].width, m_display_mode[i].height);
			}
		}
		printf("\n");
	}

	bool Window::createWindow()
	{
		al_set_new_display_flags(m_flags);

		m_display = al_create_display(m_width, m_height);

		if (!m_display)
		{
			axe::crash("Unable to create display at resolution %ix%i", m_width, m_height);
			return false;
		}

		m_width = al_get_display_width(m_display); // Get actual display resoltuion (if created with ALLEGRO_FULLSCREEN_WINDOW, passed in resolution is ignored and window is set to size of desktop)
		m_height = al_get_display_height(m_display);
	
		setWindowTitle(m_title);
		setWindowIcon(m_icon_path);

		return true;
	}

	void Window::setWindowIcon(std::string path)
	{
		if (m_flags & ALLEGRO_WINDOWED && !path.empty())
		{
			if (m_icon) al_destroy_bitmap(m_icon);

			m_icon = al_load_bitmap(path.c_str());

			if (m_icon) al_set_display_icon(m_display, m_icon);
			else
			{
				axe::log(LOGGER_WARNING, "Unable to load icon: %s\n", path.c_str());
				m_icon = nullptr;
			}
		}
	}

	void Window::setWindowTitle(std::string title)
	{
		if (m_flags & ALLEGRO_WINDOWED)
		{
			al_set_window_title(m_display, title.c_str());
		}
	}

	void Window::registerForEvents(ALLEGRO_EVENT_QUEUE *eq)
	{
		m_event_queue = eq;
		al_register_event_source(m_event_queue, al_get_display_event_source(m_display));
	}

	void Window::centerWindow(void)
	{
		al_set_window_position(m_display, al_get_display_width(m_display) / 2 - m_width / 2, al_get_display_height(m_display) / 2 - m_height / 2);
	}
}