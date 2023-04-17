#pragma once

//���� ���
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

//���� Lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

//���� Define
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define PI				3.14159265


extern shared_ptr<class DONGEngine> g_Engine;
