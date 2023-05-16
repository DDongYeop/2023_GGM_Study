#pragma once
class Actor
{
public:
	Actor() = default;
	virtual ~Actor() = default;

public:
	float	GetPosX()	{ return m_fPosX;	}
	float	GetPosY()	{ return m_fPosY;	}
	int		GetWidth()	{ return m_nWidth;	}
	int		GetHeight() { return m_nHeight; }
	float	GetScale()	{ return m_fScale;	}

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

protected:
	Actor(float x, float y, int width = 0, int height = 0, float scale = 1.0f) : m_fPosX(x), m_fPosY(y), m_nWidth(width), m_nHeight(height), m_fScale(scale) {}

protected:
	float	m_fPosX;
	float	m_fPosY;
	int		m_nWidth;
	int		m_nHeight;
	float	m_fScale;
};

