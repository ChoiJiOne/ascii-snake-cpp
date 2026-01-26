#include "GenericAssert.h"
#include "InputManager.h"

#include "Snake.h"

Snake::Snake(GameContext* ctx, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection)
	: _defaultBodyCount(defaultBodyCount)
	, _defaultMoveDirection(defaultMoveDirection)
	, _prevMoveDirection(defaultMoveDirection)
	, _currMoveDirection(defaultMoveDirection)
{
	CHECK(ctx != nullptr);
	_ctx = ctx;

	_inputMgr = InputManager::GetPtr();
	CHECK(_inputMgr != nullptr);

	_keyDirectionMap =
	{
		{ EKey::LEFT,  EMoveDirection::LEFT},
		{ EKey::RIGHT, EMoveDirection::RIGHT},
		{ EKey::UP,    EMoveDirection::UP },
		{ EKey::DOWN,  EMoveDirection::DOWN},
	};

	_isInitialized = true;
}

Snake::~Snake() {}

void Snake::Tick(float deltaSeconds)
{
	if (_ctx->IsGameOver())
	{
		return;
	}

	if (!UpdateMoveDirection())
	{
		_moveElapsedTime += deltaSeconds;
		if (_moveElapsedTime < _moveIntervalTime)
		{
			return;
		}

		EMoveResult result = Move();
		if (result == EMoveResult::BLOCKED)
		{
			_ctx->SetGameOver(true);
		}
		else
		{
			_moveElapsedTime = 0.0f;
		}
		return;
	}

	EMoveResult result = Move();
	if (result == EMoveResult::BLOCKED)
	{
		_currMoveDirection = _prevMoveDirection; // NOTE: 해당 향으로 움직일 수 없으므로, 복원.
	}
	else
	{
		_moveElapsedTime = 0.0f;
		_prevMoveDirection = _currMoveDirection;
	}
}

void Snake::Release()
{
	if (!_isInitialized)
	{
		return;
	}

	_ctx = nullptr;
	_isInitialized = false;
}

void Snake::Reset()
{
	_prevMoveDirection = _defaultMoveDirection;
	_currMoveDirection = _defaultMoveDirection;

	_head = { _ctx->GetColSize() / 2, _ctx->GetRowSize() / 2 };
	_ctx->SetTile(_head, ETile::HEAD);

	ClearBodys();
	for (int32_t count = 1; count <= _defaultBodyCount; ++count)
	{
		Position position = _head;
		position.x += (_currMoveDirection == EMoveDirection::LEFT) ? count : (_currMoveDirection == EMoveDirection::RIGHT) ? -count : 0;
		position.y += (_currMoveDirection == EMoveDirection::DOWN) ? count : (_currMoveDirection == EMoveDirection::UP) ? -count : 0;

		AddBody(position);
	}
}

void Snake::ClearBodys()
{
	_bodys.clear();
}

void Snake::AddBody(const Position& position)
{
	if (!_ctx->IsValidTile(position))
	{
		return;
	}

	_bodys.push_back(position);
	_ctx->SetTile(position, ETile::BODY);
}

bool Snake::UpdateMoveDirection()
{
	bool isUpdate = false;
	for (const auto& keyDirection : _keyDirectionMap)
	{
		const EKey& key = keyDirection.first;
		const EMoveDirection& direction = keyDirection.second;

		if (_inputMgr->GetKeyPress(key) == EPress::PRESSED && _currMoveDirection != direction)
		{
			isUpdate = true;
			_currMoveDirection = direction;
		}
	}

	return isUpdate;
}

EMoveResult Snake::Move()
{
	Position cacheHead = _head;
	EMoveResult result = _ctx->Move(_head, _currMoveDirection);
	if (result == EMoveResult::BLOCKED)
	{
		return result;
	}

	Position tail = _bodys.back();
	_bodys.pop_back();
	_bodys.push_front(cacheHead);
	_ctx->Swap(tail, cacheHead);

	if (result == EMoveResult::CONSUME)
	{
		if (!_ctx->TrySpawnFood())
		{
			_ctx->SetGameOver(true); // NOTE: 먹이를 더 이상 생성할 수 없는 상황이라면 강제 GAME OVER.
			return result;
		}

		AddBody(tail);
	}

	return result;
}