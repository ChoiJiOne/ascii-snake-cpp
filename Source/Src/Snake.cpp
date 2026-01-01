#include "ConsoleManager.h"
#include "GameAssert.h"
#include "Snake.h"

Snake::Snake(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_context = context;

	_isInitialized = true;
}

Snake::~Snake() {}

void Snake::Tick(float deltaSeconds)
{
}

void Snake::Render()
{
}

void Snake::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_consoleMgr = nullptr;
	_context = nullptr;
	_isInitialized = false;
}
