#include "ConsoleManager.h"
#include "GameAssert.h"
#include "InputManager.h"
#include "Snake.h"

Snake::Snake(GameContext* context, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection)
	: _moveDirection(defaultMoveDirection)
{
	GAME_CHECK(context != nullptr);
	_context = context;

	_inputMgr = InputManager::GetPtr();
	GAME_CHECK(_inputMgr != nullptr);
		
	_keyDirectionMap =
	{
		{ EKey::NONE,  EMoveDirection::NONE },
		{ EKey::LEFT,  EMoveDirection::LEFT},
		{ EKey::RIGHT, EMoveDirection::RIGHT},
		{ EKey::UP,    EMoveDirection::UP },
		{ EKey::DOWN,  EMoveDirection::DOWN},
	};

	_head = { _context->GetColSize() / 2, _context->GetRowSize() / 2};
	_context->SetTile(_head, ETile::HEAD);

	for (int32_t count = 1; count <= defaultBodyCount; ++count)
	{
		Position position = _head;
		position.x += (_moveDirection == EMoveDirection::LEFT) ? count : (_moveDirection == EMoveDirection::RIGHT) ? -count : 0;
		position.y += (_moveDirection == EMoveDirection::DOWN) ? count : (_moveDirection == EMoveDirection::UP) ? -count : 0;

		if (_context->IsValidTile(position))
		{
			_bodys.push_back(position);
			_context->SetTile(position, ETile::BODY);
		}
	}

	_isInitialized = true;
}

Snake::~Snake() {}

void Snake::Tick(float deltaSeconds)
{
	bool isPress = false;
	for (const auto& keyDirection : _keyDirectionMap)
	{
		const EKey& key = keyDirection.first;
		const EMoveDirection& moveDirection = keyDirection.second;

		if (_inputMgr->GetKeyPress(key) == EPress::PRESSED) //  && _moveDirection != moveDirection
		{
			isPress = true;
			_moveDirection = moveDirection;
		}
	}

	if (isPress && _context->CanMove(_head, _moveDirection))
	{
		Position cacheHead = _head;
		_context->Move(_head, _moveDirection);

		Position tail = _bodys.back();
		_bodys.pop_back();
		_bodys.push_front(cacheHead);

		_context->Swap(tail, cacheHead);
	}
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

	_context = nullptr;
	_isInitialized = false;
}
