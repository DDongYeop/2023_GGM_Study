#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f,40.f))
{}

Collider::~Collider()
{}

void Collider::Render(HDC _dc)
{
	//Core::GetInst()->GetPen(PEN_TYPE::GREEN);
	//Core::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//SelectObject();
	SelectGDI pen(_dc, PEN_TYPE::GREEN);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(m_vFinalPos.x, m_vFinalPos.y, m_vScale.x, m_vScale.y, _dc);
}

void Collider::FinalUpdate()
{
	// Object위치를 따라가야 하는거야.
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

