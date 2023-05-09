#pragma once

// 각종 Header
#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <ctime>
#include <vector>
#include <array>
#include <list>
#include <map>

#include "fmod.h"
#include "fmod.hpp"

using namespace std;

// 각종 Lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmod_vc.lib")

// 각종 Define
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define PI				3.14159265

// 싱글톤 디파인
#define DECLARE_SINGLE(type)	\
private:						\
	type() {}					\
	~type() {}					\
public:							\
	static type* GetInstance()	\
	{							\
		static type instance;	\
		return &instance;		\
	}							\

#define GET_SINGLE(type)	type::GetInstance()

// Engine Define
#define INPUT			g_Engine->GetInput()
#define TIMER			g_Engine->GetTimer()->GetDeltaTime()

extern shared_ptr<class BTSEngine> g_Engine;

// Utils Functions
wstring s2ws(const string& s);
string ws2s(const wstring& s);