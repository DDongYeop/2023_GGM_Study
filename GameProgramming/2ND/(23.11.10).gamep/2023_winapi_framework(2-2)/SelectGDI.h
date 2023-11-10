#pragma once
class SelectGDI
{
public:
	SelectGDI(HDC _dc, PEN_TYPE _ePen);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrush);
	SelectGDI(HDC _dc, HFONT _font);
	~SelectGDI();
private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;
	HFONT   m_hDefaultFont;
	HFONT	m_hFont;
};
