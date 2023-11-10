#pragma once
#include "Res.h"
class Texture :
    public Res
{
private:
    Texture();
    ~Texture();
    friend class ResMgr;
public:
    void Load(const wstring& _strFilePath);
    const int& GetWidth() const { return m_bitInfo.bmWidth; }
    const int& GetHeight() const { return m_bitInfo.bmHeight; }
    const HDC& GetDC() const { return m_hDC; }
private:
    HBITMAP m_hBit;
    HDC     m_hDC;
    BITMAP  m_bitInfo;
};

