#include "pch.h"
#include "PathMgr.h"
#include "Core.h"
void PathMgr::Init()
{
	GetCurrentDirectory(255,m_strResPath);
	wcscat_s(m_strResPath, 255, L"\\Res\\");
	SetWindowText(Core::GetInst()->GetHwnd(),m_strResPath);
}
