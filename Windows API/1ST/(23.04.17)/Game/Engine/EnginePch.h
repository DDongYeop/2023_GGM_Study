#pragma once

//각종 헤더
#include <Windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <ctime>
#include <vector>
#include <array>
#include <list>
#include <map>

using namespace std;

//각종 Lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

//각종 Define
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define PI				3.14159265


extern shared_ptr<class DONGEngine> g_Engine;
