#include "pch.h"
#include "EnginePch.h"
#include "BTSEngine.h"

shared_ptr<BTSEngine> g_Engine = NULL;

wstring s2ws(const string& s)
{
    int len;
    int slength = static_cast<int>(s.length()) + 1;
    len = ::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    ::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring ret(buf);
    delete[] buf;
    return ret;
}

string ws2s(const wstring& s)
{
    int len;
    int slength = static_cast<int>(s.length()) + 1;
    len = ::WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
    string r(len, '\0');
    ::WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
    return r;
}

float getAngle(float startX, float startY, float endX, float endY)
{
    float x = endX - startX;
    float y = endY - startY;

    float distance = sqrtf(x * x + y * y);
    float angle = acosf(x / distance);

    if (endY > startY)
    {
        angle = -angle;
        if (angle >= (float)PI * 2.0f)
            angle -= (float)PI * 2.0f;
    }
    return angle;
}

float getDistance(float startX, float startY, float endX, float endY)
{
    float x = endX - startX;
    float y = endY - startY;

    float distance = sqrtf(x * x + y * y);
    return distance;
}
