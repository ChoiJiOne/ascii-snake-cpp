#include "ConsoleManager.h"
#include "GameAssert.h"
#include "Food.h"
#include "MathUtils.h"
#include "StringUtils.h"

Food::Food(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_context = context;
	_consoleMgr = ConsoleManager::GetPtr();

	_context->TrySpawnFood();

	_countViewPosition = { 22, 3 };
	_isInitialized = true;
}

Food::~Food() {}

void Food::Tick(float deltaSeconds)
{
	int32_t count = _context->GetSpawnedFoodCount();
	if (_count != count)
	{
		_count = count;
		_isDirty = true;
	}
}

void Food::Render()
{
	if (!_isDirty)
	{
		return;
	}

	_consoleMgr->Print(_countViewPosition.x, _countViewPosition.y, StringUtils::PrintF("FOOD: %3d", _count - 1));
	_isDirty = false;
}

void Food::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}