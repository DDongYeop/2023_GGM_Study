#pragma once

class Animation;

class Image
{
public:
	Image();
	~Image();

public:
	bool					Load(wstring fileName, bool center = true);
	bool					Load(HBITMAP hBitmap, bool center = true);
	bool					Release();

public:
	bool					IsEmpty() const;
	HBITMAP					GetBitmapHandle() const;
	const BITMAP&			GetBitmapInfo() const;
	LONG					GetWidth() const;
	LONG					GetHeight() const;

	void					SetTransColor(COLORREF color);
	COLORREF				GetTransColor() const;

	void					SetCenter(BOOL center) { m_center = center; }

	void					SetX(int x) { m_posX = x; }
	int						GetX() { return m_posX; }

	void					SetY(int y) { m_posY = y; }
	int						GetY() { return m_posY; }

	RECT					GetBoundingBox();

public:
	HBITMAP					CreateAlphaBitmap(HDC hdc, int x, int y, int dest_width, int dest_height);
	HBITMAP					CreateRotateBitmap(HDC hdc, int x, int y, int dest_width, int dest_height, float angle);

public:
	void					DrawBitmap(HDC hdc, int x, int y, int dest_width = 0, int dest_height = 0);
	void					DrawBitmap(HDC hdc, int x, int y, int dest_width, int dest_height, int sx, int sy, int sw, int sh);
	void					DrawAlpha(HDC hdc, int x, int y, BYTE alpha = 255, int dest_width = 0, int dest_height = 0);
	void					DrawRotate(HDC hdc, int x, int y, float angle = 0, int dest_width = 0, int dest_height = 0);
	void					DrawLoopBitmap(HDC hdc, const LPRECT rtDraw, int offsetX, int offsetY);
	void					DrawAnimation(HDC hdc, int x, int y, shared_ptr<Animation> ani);

private:
	HBITMAP					m_hBitmap;
	BITMAP					m_bitInfo;
	BLENDFUNCTION			m_blendFunc;

	LONG					m_width;
	LONG					m_height;
	LONG					m_dest_width;
	LONG					m_dest_height;
	COLORREF				m_transColor;
	FLOAT					m_angle;
	BOOL					m_rotate;
	BOOL					m_center;

	INT						m_posX;
	INT						m_posY;
};

