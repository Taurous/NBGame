#include "..\include\SplashState.h"

#include "StateManager.h"

const axe::m_secs fade_in_time(1000);
const axe::m_secs wait_time(2000);
const axe::m_secs fade_out_time(500);
const axe::m_secs total_time(fade_in_time + wait_time + fade_out_time);

SplashState::SplashState(axe::StateManager &states, axe::InputHandler &input, axe::EventHandler &events, axe::DrawEngine &draw)
	: AbstractState(states, input, events, draw), m_alpha(0.f), m_x(0), m_y(0)
{
	m_splash_image = draw.bitmaps.getResource("splash.png");

	m_x = draw.getWindowWidth() / 2 - draw.bitmaps[m_splash_image]->getWidth() / 2;
	m_y = draw.getWindowHeight() / 2 - draw.bitmaps[m_splash_image]->getHeight() / 2;

	m_timer.start();
}

SplashState::~SplashState()
{

}

void SplashState::pause()
{
}

void SplashState::resume()
{
}

void SplashState::handleEvents()
{
	if (m_input.isKeyPressed(ALLEGRO_KEY_ESCAPE))
	{
		m_states.quit();
	}
	else if (m_input.isMousePressed(axe::MOUSE_LEFT))
	{
		//m_states.changeState(std::unique_ptr<MenuState>(m_states, m_input, m_events, m_draw));
	}
	else if (m_input.isMousePressed(axe::MOUSE_LEFT))
	{
		printf("Mouse Left Pressed\n");
	}

	if (m_timer.elapsed() > total_time + (wait_time*0.75))
	{
		m_states.quit();
		//m_states.changeState(std::unique_ptr<MenuState>(m_states, m_input, m_events, m_draw));
	}
}

void SplashState::update()
{
	auto ms = m_timer.elapsed();

	if (ms >= wait_time / 2)
	{
		ms -= wait_time / 2;

		if (ms >= total_time)
		{
			m_alpha = 0.f;
		}
		else if (ms >= fade_in_time + wait_time)
		{
			m_alpha = (std::chrono::duration<float>(fade_out_time )- (std::chrono::duration<float>(ms) - std::chrono::duration<float>(fade_in_time) - std::chrono::duration<float>(wait_time))) / std::chrono::duration<float>(fade_out_time);
		}
		else if (ms <= fade_in_time)
		{
			m_alpha = std::chrono::duration<float>(ms) / std::chrono::duration<float>(fade_in_time);
		}
	}
}

void SplashState::draw()
{
	float scale = m_alpha * 20.f;

	m_draw.drawTintedBitmap(
		m_splash_image,
		al_premul_rgba_f(1.f, 1.f, 1.f, m_alpha),
		(m_draw.getWindowWidth() / 2) - (m_draw.bitmaps[m_splash_image]->getWidth() / 2),
		(m_draw.getWindowHeight() / 2) - (m_draw.bitmaps[m_splash_image]->getHeight() / 2),
		0);
}
