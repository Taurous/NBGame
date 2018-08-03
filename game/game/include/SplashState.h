#pragma once

#include <axeLib\AbstractState.h>

class SplashState : public axe::AbstractState
{
public:
	SplashState(axe::StateManager &states, axe::InputHandler &input, axe::EventHandler &events, axe::DrawEngine &draw);
	virtual ~SplashState();

	virtual void pause();
	virtual void resume();

	virtual void handleEvents();
	virtual void update();
	virtual void draw();

private:
	axe::ResourceHandle<axe::Bitmap> m_splash_image;
	axe::Timer m_timer;

	float m_alpha;
	int m_x;
	int m_y;
};