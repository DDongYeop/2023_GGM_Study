#pragma once
#include "DONGWindow.h"

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

private:
	HDC			m_hBackDC;
	HBITMAP		m_hBitmap;

};

