#pragma once

#include "EnginePch.h"
#include "BTSEngine.h"

#pragma comment(lib, "Engine.lib")

enum class STAGE
{
	STAGE01 = 0,
	STAGE02 = 1,
	STAGE03 = 2,
	STAGE04 = 3,
	COUNT = 4
};

enum class PAWN_TYPE
{
	NONE = 0,
	PLAYER,
	ENEMY,
};