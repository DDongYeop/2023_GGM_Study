#pragma once
#include "DONGWindow.h"
#include "Timer.h"
#include "Input.h"
#include "SceneManager.h"
#include "SoundManager.h"

class DONGEngine : public DONGWindow, public enable_shared_from_this<DONGEngine>
{
public:
	DONGEngine();
	virtual ~DONGEngine();

protected:
	virtual void	Startup() override;
	virtual void	MainUpdate() override;
	virtual void	MainRender() override;
	virtual void	Cleanup() override;

protected:
	virtual void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc);
	virtual void	Release();

public:
	shared_ptr<Timer> GetTimer() { return m_timer; }
	shared_ptr<Input> GetInput() { return m_input; }

private:
	shared_ptr<Timer> m_timer;
	shared_ptr<Input> m_input;

private:
	HDC			m_hBackDC;
	HBITMAP		m_hBitmap;
};
