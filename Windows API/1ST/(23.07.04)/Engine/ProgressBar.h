#pragma once

class Image;

class ProgressBar
{
public:
	ProgressBar();
	~ProgressBar();

public:
	void Init(wstring frontImage, wstring backImage, float x, float y, int width, int height, bool bHori = true);
	void Init(shared_ptr<Image> frontImage, shared_ptr<Image> backImage, float x, float y, int width, int height, bool bHori = true);
	void Update(float dt);
	void Render(HDC hdc);
	void Release();

public:
	void SetGauge(float currentGauge, float maxGauge);
	void SetPosition(float x, float y);

private:
	float				m_posX;
	float				m_posY;
	int					m_width;
	int					m_widthGauge;
	int					m_height;
	int					m_heightGauge;
	bool				m_horizontal;

	shared_ptr<Image>	m_frontImage;
	shared_ptr<Image>	m_backImage;
};

