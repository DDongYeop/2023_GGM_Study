#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"
SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePen)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_hFont(nullptr)
{
	HPEN hColorPen = Core::GetInst()->GetPen(_ePen);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hColorPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrush)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_hFont(nullptr)
{
	HBRUSH hColorBrush = Core::GetInst()->GetBrush(_eBrush);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hColorBrush);
}

SelectGDI::SelectGDI(HDC _dc, HFONT _font)
	: m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
	, m_hDefaultFont(nullptr)
	, m_hFont(nullptr)
{
	m_hFont = _font;
	m_hDefaultFont = (HFONT)SelectObject(_dc, m_hFont);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
	SelectObject(m_hDC, m_hDefaultFont);
	if (nullptr != m_hFont)
		DeleteObject(m_hFont);
}
