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
